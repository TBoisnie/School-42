from __future__ import annotations
from abc import abstractmethod

import numpy as np

from .Layer import Layer

#
# Resources:
# - https://en.wikipedia.org/wiki/Stochastic_gradient_descent
#

#
# Optimizer
#
class Optimizer:

	@abstractmethod
	def initialize(self, layers: list[Layer]) -> None:
		pass

	@abstractmethod
	def update(self, layer: Layer) -> None:
		pass

#
# StochasticGradientDescent (SGD)
#
class StochasticGradientDescent(Optimizer):

	_learning_rate: float

	def __init__(self, learning_rate: float):
		self._learning_rate = learning_rate

	def initialize(self, _: list[Layer]) -> None:
		pass

	def update(self, layer: Layer) -> None:
		layer.set_weights(layer.get_weights() - self._learning_rate * layer.get_weights_gradients())
		layer.set_biases(layer.get_biases() - self._learning_rate * layer.get_biases_gradients())

#
# Momentum
#
class Momentum(Optimizer):

	_learning_rate: float
	_momentum: float

	_weights_velocity: dict[Layer, np.ndarray]
	_biases_velocity: dict[Layer, np.ndarray]

	def __init__(self, learning_rate: float, momentum: float):
		assert 0. <= momentum <= 1., \
			"Optimizer::Momentum: `momentum` must be between 0 and 1."

		self._learning_rate = learning_rate
		self._momentum = momentum

		self._weights_velocity = {}
		self._biases_velocity = {}

	def initialize(self, layers: list[Layer]) -> None:
		for layer in layers:
			self._weights_velocity[layer] = np.zeros_like(layer.get_weights())
			self._biases_velocity[layer] = np.zeros_like(layer.get_biases())

	def update(self, layer: Layer) -> None:
		assert layer in self._weights_velocity, \
			"Optimizer::Momentum::update: `layer` was not in the initialization list."

		self._weights_velocity[layer] = self._momentum * self._weights_velocity[layer] - self._learning_rate * layer.get_weights_gradients()
		self._biases_velocity[layer] = self._momentum * self._biases_velocity[layer] - self._learning_rate * layer.get_biases_gradients()

		layer.set_weights(layer.get_weights() + self._weights_velocity[layer])
		layer.set_biases(layer.get_biases() + self._biases_velocity[layer])

#
# NesterovMomentum
#
class NesterovMomentum(Optimizer):

	_learning_rate: float
	_momentum: float

	_weights_velocity: dict[Layer, np.ndarray]
	_biases_velocity: dict[Layer, np.ndarray]

	def __init__(self, learning_rate: float, momentum: float):
		assert 0. <= momentum <= 1., \
			"Optimizer::NesterovMomentum: `momentum` must be between 0 and 1."

		self._learning_rate = learning_rate
		self._momentum = momentum

		self._weights_velocity = {}
		self._biases_velocity = {}

	def initialize(self, layers: list[Layer]) -> None:
		for layer in layers:
			self._weights_velocity[layer] = np.zeros_like(layer.get_weights())
			self._biases_velocity[layer]  = np.zeros_like(layer.get_biases())

	def update(self, layer: Layer) -> None:
		assert layer in self._weights_velocity, \
			"Optimizer::NesterovMomentum::update: `layer` was not in the initialization list."

		prev_weights_velocity = self._weights_velocity[layer]
		prev_biases_velocity  = self._biases_velocity[layer]

		self._weights_velocity[layer] = self._momentum * self._weights_velocity[layer] - self._learning_rate * layer.get_weights_gradients()
		self._biases_velocity[layer] = self._momentum * self._biases_velocity[layer] - self._learning_rate * layer.get_biases_gradients()

		layer.set_weights(layer.get_weights() - self._momentum * prev_weights_velocity + (1 + self._momentum) * self._weights_velocity[layer])
		layer.set_biases(layer.get_biases() - self._momentum * prev_biases_velocity + (1 + self._momentum) * self._biases_velocity[layer])

#
# AdaptiveGradient (AdaGrad)
#
class AdaptiveGradient(Optimizer):

	_learning_rate: float
	_epsilon: float

	_weights_grad_squared: dict[Layer, np.ndarray]
	_biases_grad_squared: dict[Layer, np.ndarray]

	def __init__(self, learning_rate: float, epsilon: float = 1e-15):
		self._learning_rate = learning_rate
		self._epsilon = epsilon

		self._weights_grad_squared = {}
		self._biases_grad_squared = {}

	def initialize(self, layers: list[Layer]) -> None:
		for layer in layers:
			self._weights_grad_squared[layer] = np.zeros_like(layer.get_weights())
			self._biases_grad_squared[layer]  = np.zeros_like(layer.get_biases())

	def update(self, layer: Layer) -> None:
		assert layer in self._weights_grad_squared, \
			"Optimizer::AdaptiveGradient::update: `layer` was not in the initialization list."

		self._weights_grad_squared[layer] += np.square(layer.get_weights_gradients())
		self._biases_grad_squared[layer] += np.square(layer.get_biases_gradients())

		layer.set_weights(layer.get_weights() - self._learning_rate / (np.sqrt(self._weights_grad_squared[layer]) + self._epsilon) * layer.get_weights_gradients())
		layer.set_biases(layer.get_biases() - self._learning_rate / (np.sqrt(self._biases_grad_squared[layer]) + self._epsilon) * layer.get_biases_gradients())

#
# RootMeanSquarePropagation (RMSProp)
#
class RootMeanSquarePropagation(Optimizer):

	_learning_rate: float
	_decay_rate: float
	_epsilon: float

	_weights_grad_squared_avg: dict[Layer, np.ndarray]
	_biases_grad_squared_avg: dict[Layer, np.ndarray]

	def __init__(self, learning_rate: float, decay_rate: float, epsilon: float = 1e-15):
		self._learning_rate = learning_rate
		self._decay_rate = decay_rate
		self._epsilon = epsilon

		self._weights_grad_squared_avg = {}
		self._biases_grad_squared_avg = {}

	def initialize(self, layers: list[Layer]) -> None:
		for layer in layers:
			self._weights_grad_squared_avg[layer] = np.zeros_like(layer.get_weights())
			self._biases_grad_squared_avg[layer]  = np.zeros_like(layer.get_biases())

	def update(self, layer: Layer) -> None:
		assert layer in self._weights_grad_squared_avg, \
			"Optimizer::RootMeanSquarePropagation::update: `layer` was not in the initialization list."

		self._weights_grad_squared_avg[layer] = self._decay_rate * self._weights_grad_squared_avg[layer] + (1 - self._decay_rate) * np.square(layer.get_weights_gradients())
		self._biases_grad_squared_avg[layer]  = self._decay_rate * self._biases_grad_squared_avg[layer]  + (1 - self._decay_rate) * np.square(layer.get_biases_gradients())

		layer.set_weights(layer.get_weights() - self._learning_rate / (np.sqrt(self._weights_grad_squared_avg[layer]) + self._epsilon) * layer.get_weights_gradients())
		layer.set_biases(layer.get_biases() - self._learning_rate / (np.sqrt(self._biases_grad_squared_avg[layer]) + self._epsilon) * layer.get_biases_gradients())
