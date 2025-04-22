from __future__ import annotations
from abc import ABC, abstractmethod

import numpy as np

from .Activation import Activation
from .Random import Random, Constant, Uniform

#
# Layer
#
class Layer:

	@abstractmethod
	def forward(self, X: np.ndarray) -> np.ndarray:
		pass

	@abstractmethod
	def backward(self, y: np.ndarray) -> np.ndarray:
		pass

	@abstractmethod
	def get_weights(self) -> np.ndarray:
		pass

	@abstractmethod
	def set_weights(self, weights: np.ndarray) -> Layer:
		pass

	@abstractmethod
	def get_biases(self) -> np.ndarray:
		pass

	@abstractmethod
	def set_biases(self, biases: np.ndarray) -> Layer:
		pass

	@abstractmethod
	def get_weights_gradients(self) -> np.ndarray:
		pass

	@abstractmethod
	def get_biases_gradients(self) -> np.ndarray:
		pass

#
# LayerBase
#
class LayerBase(ABC, Layer):

	_weights: np.ndarray
	_biases: np.ndarray

	_weights_grad: np.ndarray
	_biases_grad: np.ndarray

	def __init__(self):
		self._weights = None
		self._weights_grad = None
		self._biases = None
		self._biases_grad = None

	def get_weights(self) -> np.ndarray:
		return self._weights

	def set_weights(self, weights: np.ndarray) -> LayerBase:
		self._weights = weights
		return self

	def get_biases(self) -> np.ndarray:
		return self._biases

	def set_biases(self, biases: np.ndarray) -> LayerBase:
		self._biases = biases
		return self

	def get_weights_gradients(self) -> np.ndarray:
		return self._weights_grad

	def get_biases_gradients(self) -> np.ndarray:
		return self._biases_grad

#
# Dense
#
class Dense(LayerBase):

	_shape: tuple[int, int]
	_activation: Activation

	_X: np.ndarray
	_z: np.ndarray
	_y: np.ndarray

	def __init__(self, shape: tuple[int, int], activation: Activation, weight_initializer: Random = Uniform(), biases_initializer: Random = Constant(0.)):
		self._shape = shape
		self._activation = activation

		self._weights = weight_initializer.next(shape)
		self._biases = biases_initializer.next((1, shape[1]))

	def forward(self, X: np.ndarray) -> np.ndarray:
		self._X = X
		self._z = np.dot(X, self._weights) + self._biases
		self._y = self._activation.activate(self._z)

		return self._y

	def backward(self, y: np.ndarray) -> np.ndarray:
		batch_size = y.shape[0]

		d_y = self._activation.gradient(y)

		# Note: Is dividing by `batch_size` required ?
		self._weights_grad = np.dot(self._X.T, d_y) / batch_size
		self._biases_grad = np.sum(d_y, axis=0, keepdims=True) / batch_size

		return np.dot(d_y, self._weights.T)
