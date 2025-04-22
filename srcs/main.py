from argparse import ArgumentParser
from typing import Literal
from enum import IntEnum
from os import path

import numpy as np

from lib.fmt.Csv import CsvFile
from lib.fmt.Json import JsonFile
from lib.ai.Model import Model, Perceptron
from lib.ai.Layer import Dense
from lib.ai.Activation import ReLU, SoftMax
from lib.ai.Loss import BinaryCrossEntropy, CategoricalCrossEntropy
from lib.ai.Optimizer import StochasticGradientDescent, AdaptiveGradient, NesterovMomentum, RootMeanSquarePropagation
from lib.ai.Random import HeUniform
from lib.ai.Serializer import Serializer
from lib.ai.Factory import ModelFactory
from lib.ds.DataSet import DataSet
from lib.ds.Storage import Storage, InMemoryStorage
from lib.ui.UserInterface import UserInterface


#
# Config
#
CONFIG = {
	'fit': {
		'epochs': 1500,
		'batch_size': 128,
		'loss_threshold': 0.05,
	},
	'store': {
		'gap': 200,
		'epochs': [],
	},
}

CONFIG['store']['epochs'] = list(range(0, CONFIG['fit']['epochs'], CONFIG['store']['gap'])) + [ CONFIG['fit']['epochs'] - 1 ]

#
# Model
#
def _model(version: Literal['main', 'alt'] = 'main', seed: int = None) -> Perceptron:
	if seed is not None:
		np.random.seed(seed)
		print(f"Seed: {seed}")

	weight_initializer = HeUniform(seed)

	match version:
		case 'main':
			return Perceptron(
				layers=[
					Dense(shape=(30, 24), activation=ReLU(),    weight_initializer=weight_initializer),
					Dense(shape=(24, 12), activation=ReLU(),    weight_initializer=weight_initializer),
					Dense(shape=(12,  6), activation=ReLU(),    weight_initializer=weight_initializer),
					Dense(shape=( 6,  2), activation=SoftMax(), weight_initializer=weight_initializer),
				],
				optimizer=AdaptiveGradient(learning_rate=0.01),
				loss=BinaryCrossEntropy(),
			)
		case 'alt':
			return Perceptron(
				layers=[
					Dense(shape=(30, 24), activation=ReLU(),    weight_initializer=weight_initializer),
					Dense(shape=(24, 12), activation=ReLU(),    weight_initializer=weight_initializer),
					Dense(shape=(12,  6), activation=ReLU(),    weight_initializer=weight_initializer),
					Dense(shape=( 6,  2), activation=SoftMax(), weight_initializer=weight_initializer),
				],
				optimizer=NesterovMomentum(learning_rate=0.1, momentum=0.9),
				loss=BinaryCrossEntropy(),
			)

#
# Accuracy
#
def _accuracy(y_pred: np.ndarray, y_true: np.ndarray) -> float:
	return np.sum((y_pred - y_true) == 0) / y_true.size * 100

#
# Correctness
#
def _correctness(y_pred: np.ndarray, y_true: np.ndarray) -> dict[str, int]:
	difference = y_pred - y_true
	return {
		'false_negative': np.sum(difference == -1),
		'correct':        np.sum(difference ==  0),
		'false_positive': np.sum(difference ==  1),
	}

#
# FlattenOutput
#
def _flatten_output(y: np.ndarray) -> np.ndarray:
	return np.argmax(y, axis=1, keepdims=True).flatten() if y.ndim >= 2 else np.round(y)

#
# OnEpochStoreAndPrintStats
#
def _on_epoch_store_and_print_stats(model: Model, store: Storage, X: np.ndarray, y: np.ndarray, prefix: str = ""):
	def _store(event) -> None:
		y_pred = model.predict(X)
		y_true = y

		# Flatten
		y_pred = _flatten_output(y_pred)
		y_true = _flatten_output(y_true)

		# Stats
		loss, accuracy, correctness = model.loss(X, y), _accuracy(y_pred, y_true), _correctness(y_pred, y_true)

		# Store
		store.push('loss', loss)
		store.push('accuracy', accuracy)

		if event['epoch'] in CONFIG['store']['epochs']:
			store.push('correctness', correctness)

		# Print
		print(f"{prefix}Epoch {event['epoch']:5}: Loss {loss:<10.6} Accuracy {accuracy:<8.6} Correctness (C) {correctness['correct']:3} (FP) {correctness['false_positive']:3} (FN) {correctness['false_negative']:3}")

	return _store

#
# Type
#
class Type(IntEnum):
	BENIGN = 0
	MALIGNANT = 1

#
# Describe
#
def describe(data_path: str) -> None:
	# Load file
	file = CsvFile(data_path).load()
	dataset = DataSet(np.array(file.get_content()), index=True)

	# Format values
	dataset.content[ dataset.content == 'B' ] = Type.BENIGN.value
	dataset.content[ dataset.content == 'M' ] = Type.MALIGNANT.value

	dataset.set_type(float)

	# Split by type
	benign_X = dataset.content[ dataset.content[:, 0] == Type.BENIGN.value, 1: ]
	malign_X = dataset.content[ dataset.content[:, 0] == Type.MALIGNANT.value, 1: ]

	# Display
	ui = UserInterface()
	w = ui.create_grid_window(3, 10)

	for row in range(3):
		for column in range(10):
			w.create_multigraph(row, column).set_title(f"Feature {row * 10 + column}")\
				.add_hist(benign_X[:, row * 10 + column], "Benign")\
				.add_hist(malign_X[:, row * 10 + column], "Malignant")\
				.enable_legends()

	ui.show()

#
# Split
#
def split(data_path: str, percent: float) -> tuple[str, str]:
	# Load file
	file = CsvFile(data_path).load()
	dataset = DataSet(np.array(file.get_content()), index=True)

	# Shuffle and Split
	train_dataset, valid_dataset = dataset.split(percent)

	# File names
	file_name, file_ext = path.splitext(data_path)

	train_file_name = f"{file_name}.train{file_ext}"
	valid_file_name = f"{file_name}.valid{file_ext}"

	# Save
	CsvFile(train_file_name).set_content(train_dataset.raw_data.tolist()).save()
	CsvFile(valid_file_name).set_content(valid_dataset.raw_data.tolist()).save()

	print(f"> Data splitted at {percent}% ({train_dataset.shape[0]}/{dataset.shape[0]})")

	return (train_file_name, valid_file_name)

#
# Train
#
def train(data_path: str, model_path: str, seed: int) -> None:
	# Load file
	file = CsvFile(data_path).load()
	dataset = DataSet(np.array(file.get_content()), index=True)

	# Replace B/M by 0/1
	dataset.content[ dataset.content == 'B' ] = Type.BENIGN.value
	dataset.content[ dataset.content == 'M' ] = Type.MALIGNANT.value

	# Set data type
	dataset.set_type(float)

	# Add complementary column since SoftMax is required by subject
	column = dataset.content[:, 0].copy()
	column[ dataset.content[:, 0] == Type.BENIGN.value ] = Type.MALIGNANT.value
	column[ dataset.content[:, 0] == Type.MALIGNANT.value ] = Type.BENIGN.value
	# Position = 1 to match 0/1 (B/M), with index ([1, 0] -> Begnin, [0, 1] -> Malignant)
	dataset.add(column, position=1, axis=DataSet.Axis.COLUMN)

	# Normalize
	dataset.normalize()

	# Split features/labels
	X, y = dataset.content[:, 2:], dataset.content[:, :2]

	# Setup
	store = InMemoryStorage()

	model = _model('main', seed)
	model.on('epoch', _on_epoch_store_and_print_stats(model, store, X, y))

	# Train
	model.fit(X, y, **CONFIG['fit'])

	# Export
	JsonFile(model_path).set_content(Serializer().serialize(model)).save()

	print(f"> Model saved into \"{model_path}\"")

	# Display
	ui = UserInterface()
	w = ui.create_grid_window(3, 1, title="Training Stats")

	w.create_multigraph(0, 0)\
		.add_line(y=store.get('loss'), label="Loss")\
		.set_label('x', "Epoch")\
		.set_label('y', "Loss")\
		.enable_legends()
	w.create_multigraph(1, 0)\
		.add_line(y=store.get('accuracy'), label="Accuracy")\
		.set_label('x', "Epoch")\
		.set_label('y', "Accuracy")\
		.enable_legends()
	w.create_multigraph(2, 0)\
		.add_stacked_bars(y=store.get('correctness'))\
		.set_label('x', f"Epoch (x{CONFIG['store']['gap']})")\
		.set_label('y', "Correctness")\
		.enable_legends()

	ui.show()

#
# Predict
#
def predict(data_path: str, model_path: str) -> None:
	# Load file
	file = CsvFile(data_path).load()
	dataset = DataSet(np.array(file.get_content()), index=True)

	# Replace B/M by 0/1
	dataset.content[ dataset.content == 'B' ] = Type.BENIGN.value
	dataset.content[ dataset.content == 'M' ] = Type.MALIGNANT.value

	# Set data type
	dataset.set_type(float)

	# Add complementary column since SoftMax is required by subject
	column = dataset.content[:, 0].copy()
	column[ dataset.content[:, 0] == Type.BENIGN.value ] = Type.MALIGNANT.value
	column[ dataset.content[:, 0] == Type.MALIGNANT.value ] = Type.BENIGN.value
	# Position = 1 to match 0/1 (B/M), with index ([1, 0] -> Begnin, [0, 1] -> Malignant)
	dataset.add(column, position=1, axis=DataSet.Axis.COLUMN)

	# Normalize
	dataset.normalize()

	# Split features/labels
	X, y = dataset.content[:, 2:], dataset.content[:, :2]

	# Setup
	model = ModelFactory.from_json(JsonFile(model_path).load().get_content())

	y_pred = model.predict(X)

	# Stats
	y_pred = _flatten_output(y_pred)
	y_true = _flatten_output(y)

	loss = model.loss(X, y)
	accuracy = _accuracy(y_pred, y_true)
	correctness = _correctness(y_pred, y_true)

	print(f"Prediction: Loss {loss:<10.6} Accuracy {accuracy:<8.6} Correctness (C) {correctness['correct']:3} (FP) {correctness['false_positive']:3} (FN) {correctness['false_negative']:3}")

	# Display
	ui = UserInterface()
	ui.create_grid_window(title="Prediction")\
		.create_multigraph()\
		.add_bars(y=y_pred, label="Prediction")\
		.add_bars(y=np.abs(y_pred - y_true), label="Different")\
		.set_label('x', "Index")\
		.set_label('y', "Positiveness")\
		.enable_legends()
	ui.show()

#
# All (Training + Validation)
#
def all(data_path: str, model_path: str, percent: float, seed: int) -> None:
	# Load file
	file = CsvFile(data_path).load()
	dataset = DataSet(np.array(file.get_content()), index=True)

	# Replace B/M by 0/1
	dataset.content[ dataset.content == 'B' ] = Type.BENIGN.value
	dataset.content[ dataset.content == 'M' ] = Type.MALIGNANT.value

	# Set data type
	dataset.set_type(float)

	# Add complementary column since SoftMax is required by subject
	column = dataset.content[:, 0].copy()
	column[ dataset.content[:, 0] == Type.BENIGN.value ] = Type.MALIGNANT.value
	column[ dataset.content[:, 0] == Type.MALIGNANT.value ] = Type.BENIGN.value
	# Position = 1 to match 0/1 (B/M), with index ([1, 0] -> Begnin, [0, 1] -> Malignant)
	dataset.add(column, position=1, axis=DataSet.Axis.COLUMN)

	# Split training/validation
	train_dataset, valid_dataset = dataset.split(percent)

	# Normalize
	train_dataset.normalize()
	valid_dataset.normalize()

	# Split features/labels
	train_X, train_y = train_dataset.content[:, 2:], train_dataset.content[:, :2]
	valid_X, valid_y = valid_dataset.content[:, 2:], valid_dataset.content[:, :2]

	# Setup
	train_store = InMemoryStorage()
	valid_store = InMemoryStorage()

	model = _model('main', seed)
	model.on('epoch', _on_epoch_store_and_print_stats(model, train_store, train_X, train_y, "(Train) "))
	model.on('epoch', _on_epoch_store_and_print_stats(model, valid_store, valid_X, valid_y, "(Valid) "))

	# Train
	model.fit(train_X, train_y, **CONFIG['fit'])

	# Export
	JsonFile(model_path).set_content(Serializer().serialize(model)).save()

	print(f"> Model saved into \"{model_path}\"")

	# Display
	ui = UserInterface()
	w = ui.create_grid_window(4, 1, title="Training Stats")

	w.create_multigraph(0, 0, column_span=2)\
		.add_line(y=train_store.get('loss'), label="Training Loss")\
		.add_line(y=valid_store.get('loss'), label="Validation Loss")\
		.set_label('x', "Epoch")\
		.set_label('y', "Loss")\
		.enable_legends()
	w.create_multigraph(1, 0, column_span=2)\
		.add_line(y=train_store.get('accuracy'), label="Training Accuracy")\
		.add_line(y=valid_store.get('accuracy'), label="Validation Accuracy")\
		.set_label('x', "Epoch")\
		.set_label('y', "Accuracy")\
		.enable_legends()
	w.create_multigraph(2, 0)\
		.add_stacked_bars(y=train_store.get('correctness'))\
		.set_label('x', f"Epoch (x{CONFIG['store']['gap']})")\
		.set_label('y', "Training Correctness")\
		.enable_legends()
	w.create_multigraph(3, 0)\
		.add_stacked_bars(y=valid_store.get('correctness'))\
		.set_label('x', f"Epoch (x{CONFIG['store']['gap']})")\
		.set_label('y', "Validation Correctness")\
		.enable_legends()

	ui.show()

#
# Compare
#
def compare(data_path: str, percent: float, seed: int) -> None:
	# Load file
	file = CsvFile(data_path).load()
	dataset = DataSet(np.array(file.get_content()), index=True)

	# Replace B/M by 0/1
	dataset.content[ dataset.content == 'B' ] = Type.BENIGN.value
	dataset.content[ dataset.content == 'M' ] = Type.MALIGNANT.value

	# Set data type
	dataset.set_type(float)

	# Add complementary column since SoftMax is required by subject
	column = dataset.content[:, 0].copy()
	column[ dataset.content[:, 0] == Type.BENIGN.value ] = Type.MALIGNANT.value
	column[ dataset.content[:, 0] == Type.MALIGNANT.value ] = Type.BENIGN.value
	# Position = 1 to match 0/1 (B/M), with index ([1, 0] -> Begnin, [0, 1] -> Malignant)
	dataset.add(column, position=1, axis=DataSet.Axis.COLUMN)

	# Normalize
	dataset.normalize()

	# Split training/validation
	train_dataset, valid_dataset = dataset.split(percent)

	# Split features/labels
	train_X, train_y = train_dataset.content[:, 2:], train_dataset.content[:, :2]
	valid_X, valid_y = valid_dataset.content[:, 2:], valid_dataset.content[:, :2]

	# Setup
	train_store = InMemoryStorage()
	valid_store = InMemoryStorage()

	model = _model('main', seed)
	model.on('epoch', _on_epoch_store_and_print_stats(model, train_store, train_X, train_y, "(Train) "))
	model.on('epoch', _on_epoch_store_and_print_stats(model, valid_store, valid_X, valid_y, "(Valid) "))

	# Train
	model.fit(train_X, train_y, **CONFIG['fit'])

	# Setup Alt
	train_store_alt = InMemoryStorage()
	valid_store_alt = InMemoryStorage()

	model_alt = _model('alt', seed)
	model_alt.on('epoch', _on_epoch_store_and_print_stats(model_alt, train_store_alt, train_X, train_y, "(Train Alt) "))
	model_alt.on('epoch', _on_epoch_store_and_print_stats(model_alt, valid_store_alt, valid_X, valid_y, "(Valid Alt) "))

	# Train Alt
	model_alt.fit(train_X, train_y, **CONFIG['fit'])

	# Display
	ui = UserInterface()
	w = ui.create_grid_window(4, 2, title="Training Stats")

	w.create_multigraph(0, 0, column_span=2)\
		.add_line(y=train_store.get('loss'), label="Training Loss")\
		.add_line(y=valid_store.get('loss'), label="Validation Loss")\
		.add_line(y=train_store_alt.get('loss'), label="Training Alt Loss")\
		.add_line(y=valid_store_alt.get('loss'), label="Validation Alt Loss")\
		.set_label('x', "Epoch")\
		.set_label('y', "Loss")\
		.enable_legends()
	w.create_multigraph(1, 0, column_span=2)\
		.add_line(y=train_store.get('accuracy'), label="Training Accuracy")\
		.add_line(y=valid_store.get('accuracy'), label="Validation Accuracy")\
		.add_line(y=train_store_alt.get('accuracy'), label="Training Alt Accuracy")\
		.add_line(y=valid_store_alt.get('accuracy'), label="Validation Alt Accuracy")\
		.set_label('x', "Epoch")\
		.set_label('y', "Accuracy")\
		.enable_legends()
	w.create_multigraph(2, 0)\
		.add_stacked_bars(y=train_store.get('correctness'))\
		.set_label('x', f"Epoch (x{CONFIG['store']['gap']})")\
		.set_label('y', "Training Correctness")\
		.enable_legends()
	w.create_multigraph(3, 0)\
		.add_stacked_bars(y=valid_store.get('correctness'))\
		.set_label('x', f"Epoch (x{CONFIG['store']['gap']})")\
		.set_label('y', "Validation Correctness")\
		.enable_legends()
	w.create_multigraph(2, 1)\
		.add_stacked_bars(y=train_store_alt.get('correctness'))\
		.set_label('x', f"Epoch (x{CONFIG['store']['gap']})")\
		.set_label('y', "Training Alt Correctness")\
		.enable_legends()
	w.create_multigraph(3, 1)\
		.add_stacked_bars(y=valid_store_alt.get('correctness'))\
		.set_label('x', f"Epoch (x{CONFIG['store']['gap']})")\
		.set_label('y', "Validation Alt Correctness")\
		.enable_legends()

	ui.show()

#
# Main
#
if __name__ == '__main__':
	try:
		ROOT = path.join(path.dirname(path.abspath(__file__)), '..')

		parser = ArgumentParser()
		parser.add_argument("--action", choices=['describe', 'split', 'train', 'predict', 'all', 'compare'], default='all')
		parser.add_argument("--model", default=path.join(ROOT, 'assets', 'model.json'))
		parser.add_argument("--data", default=path.join(ROOT, 'assets', 'data.csv'))
		parser.add_argument("--percent", type=int, choices=range(1, 100), default=80)
		parser.add_argument("--seed", type=int, default=None)
		args = parser.parse_args()

		match args.action:
			case 'describe':
				describe(args.data)
			case 'split':
				split(args.data, args.percent)
			case 'train':
				train(args.data, args.model, args.seed)
			case 'predict':
				predict(args.data, args.model)
			case 'all':
				all(args.data, args.model, args.percent, args.seed)
			case 'compare':
				compare(args.data, args.percent, args.seed)
			case _:
				print("Error: Action Not Supported")
	except Exception as e:
		print("Main:Exception:", e)
	except:
		pass
