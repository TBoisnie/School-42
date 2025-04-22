from __future__ import annotations
from abc import abstractmethod

import numpy as np

from lib.event.Observable import Observable
from .Layer import Layer
from .Loss import ClassificationLoss
from .Optimizer import Optimizer

#
# Model
#
class Model:

	@abstractmethod
	def fit(self, X: np.ndarray, y: np.ndarray, epochs: int, batch_size: int) -> None:
		pass

	@abstractmethod
	def predict(self, X: np.ndarray) -> np.ndarray:
		pass

	@abstractmethod
	def loss(self, X: np.ndarray, y: np.ndarray) -> float:
		pass

#
# Perceptron
#
class Perceptron(Model, Observable):

	_layers: list[Layer]
	_loss: ClassificationLoss
	_optimizer: Optimizer

	def __init__(self, layers: list[Layer], loss: ClassificationLoss, optimizer: Optimizer):
		assert len(layers) > 0, \
			"Model::Perceptron: At least 1 layer is required."

		super().__init__()

		self._layers = layers
		self._loss = loss
		self._optimizer = optimizer

		self._optimizer.initialize(self._layers)

	def fit(self, X: np.ndarray, y: np.ndarray, epochs: int = 100, batch_size: int = 8, loss_threshold: float = 1e-4) -> None:
		assert len(X) == len(y), \
			"Model::Perceptron: `X` and `y` must have the same length."
		assert epochs > 0, \
			"Model::Perceptron: `epochs` must be > 0."
		assert batch_size > 0, \
			"Model::Perceptron: `batch_size` must be > 0."

		sample_size = X.shape[0]

		for epoch in range(epochs):
			indexes = np.random.permutation(sample_size)

			X_shuffled = X[indexes]
			y_shuffled = y[indexes]

			for i in range(0, sample_size, batch_size):
				X_batch = X_shuffled[i:i+batch_size]
				y_batch = y_shuffled[i:i+batch_size]

				y_pred = self._forward(X_batch)

				self._backward(y_pred, y_batch)
				self._update()

			loss = self.loss(X, y)
			self.emit('epoch', { 'epoch': epoch, 'loss': loss })

			if loss <= loss_threshold:
				self.emit('early_stop', { 'epoch': epoch })
				return

	def predict(self, X: np.ndarray) -> np.ndarray:
		return self._loss.classify(self._forward(X))

	def loss(self, X: np.ndarray, y: np.ndarray) -> float:
		return self._loss.calculate(self._forward(X), y)

	def _forward(self, X: np.ndarray) -> np.ndarray:
		for layer in self._layers:
			X = layer.forward(X)
		return X

	def _backward(self, y_pred: np.ndarray, y_true: np.ndarray) -> None:
		y = self._loss.gradient(y_pred, y_true)
		for layer in reversed(self._layers):
			y = layer.backward(y)

	def _update(self) -> None:
		for layer in self._layers:
			self._optimizer.update(layer)
