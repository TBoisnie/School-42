from __future__ import annotations
from abc import abstractmethod

import numpy as np


#
# Activation
#
# - https://en.wikipedia.org/wiki/Activation_function
#
class Activation:

	@abstractmethod
	def activate(self, z: np.ndarray) -> np.ndarray:
		pass

	@abstractmethod
	def gradient(self, y: np.ndarray) -> np.ndarray:
		pass

#
# Identity
#
class Identity(Activation):

	def activate(self, z: np.ndarray) -> np.ndarray:
		return z

	def gradient(self, y: np.ndarray) -> np.ndarray:
		return y

#
# ReLU (Rectified Linear Unit)
#
class ReLU(Activation):

	_a: np.ndarray

	def activate(self, z: np.ndarray) -> np.ndarray:
		self._a = np.maximum(0., z)
		return self._a

	def gradient(self, y: np.ndarray) -> np.ndarray:
		return y * np.where(self._a < 0., 0., 1.)

#
# TanH
#
class TanH(Activation):

	_a: np.ndarray

	def activate(self, z: np.ndarray) -> np.ndarray:
		self._a = np.tanh(z)
		return self._a

	def gradient(self, y: np.ndarray) -> np.ndarray:
		return y * (1. - self._a ** 2)

#
# Sigmoid
#
class Sigmoid(Activation):

	_a: np.ndarray

	def activate(self, z: np.ndarray) -> np.ndarray:
		self._a = 1. / (1. + np.exp(-z))
		return self._a

	def gradient(self, y: np.ndarray) -> np.ndarray:
		return y * self._a * (1. - self._a)

#
# SoftMax
#
class SoftMax(Activation):

	_a: np.ndarray

	def activate(self, z: np.ndarray) -> np.ndarray:
		# Subtract max for stability
		exp_z = np.exp(z - np.max(z, axis=1, keepdims=True))

		self._a = exp_z / np.sum(exp_z, axis=1, keepdims=True)

		return self._a

	def gradient(self, y: np.ndarray) -> np.ndarray:
		d_z = np.empty_like(y)

		for i in range(y.shape[0]):
			jacobian_matrix = np.diag(self._a[i]) - np.outer(self._a[i], self._a[i])
			d_z[i] = np.dot(jacobian_matrix, y[i])

		return d_z
