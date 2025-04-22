from __future__ import annotations
from abc import abstractmethod

import numpy as np


#
# Resources:
# - https://www.datacamp.com/tutorial/loss-function-in-machine-learning
#

#
# Loss
#
class Loss:

	@abstractmethod
	def calculate(self, y_pred: np.ndarray, y_true: np.ndarray) -> float:
		pass

	@abstractmethod
	def gradient(self, y_pred: np.ndarray, y_true: np.ndarray) -> np.ndarray:
		pass

#
# RegressionLoss
#
class RegressionLoss(Loss):
	pass

#
# MeanSquaredError (MSE)
#
class MeanSquaredError(RegressionLoss):

	def calculate(self, y_pred: np.ndarray, y_true: np.ndarray) -> float:
		return np.mean((y_pred - y_true) ** 2)

	def gradient(self, y_pred: np.ndarray, y_true: np.ndarray) -> np.ndarray:
		return 2 * (y_pred - y_true) / y_true.shape[0]

#
# MeanAbsoluteError (MAE)
#
class MeanAbsoluteError(RegressionLoss):

	def calculate(self, y_pred: np.ndarray, y_true: np.ndarray) -> float:
		return np.mean(np.abs(y_pred - y_true))

	def gradient(self, y_pred: np.ndarray, y_true: np.ndarray) -> np.ndarray:
		return np.sign(y_pred - y_true)

#
# ClassificationLoss
#
class ClassificationLoss(Loss):

	@abstractmethod
	def classify(self, y_pred: np.ndarray) -> np.ndarray:
		pass

#
# BinaryCrossEntropy (BCE)
#
class BinaryCrossEntropy(ClassificationLoss):

	_epsilon: float

	def __init__(self, epsilon: float = 1e-15):
		self._epsilon = epsilon

	def calculate(self, y_pred: np.ndarray, y_true: np.ndarray) -> float:
		# Clip to prevent log(0)
		y_pred = np.clip(y_pred, self._epsilon, 1 - self._epsilon)
		return -np.mean(y_true * np.log(y_pred) + (1 - y_true) * np.log(1 - y_pred))

	def gradient(self, y_pred: np.ndarray, y_true: np.ndarray) -> np.ndarray:
		# Clip to prevent log(0)
		y_pred = np.clip(y_pred, self._epsilon, 1 - self._epsilon)
		return (y_pred - y_true) / (y_pred * (1 - y_pred) * y_true.shape[0])

	def classify(self, y_pred: np.ndarray) -> np.ndarray:
		return np.round(y_pred)

#
# CategoricalCrossEntropy (CCE)
#
class CategoricalCrossEntropy(ClassificationLoss):

	_epsilon: float

	def __init__(self, epsilon: float = 1e-15):
		self._epsilon = epsilon

	def calculate(self, y_pred: np.ndarray, y_true: np.ndarray) -> float:
		# Clip to prevent log(0)
		y_pred = np.clip(y_pred, self._epsilon, 1 - self._epsilon)
		return -np.mean(np.sum(y_true * np.log(y_pred), axis=1))

	def gradient(self, y_pred: np.ndarray, y_true: np.ndarray) -> np.ndarray:
		# Clip to prevent log(0)
		y_pred = np.clip(y_pred, self._epsilon, 1 - self._epsilon)
		return (y_pred - y_true) / y_true.shape[0]

	def classify(self, y_pred: np.ndarray) -> np.ndarray:
		return np.argmax(y_pred, axis=1)
