from __future__ import annotations
from abc import abstractmethod

import numpy as np

#
# Resources:
# - https://pyimagesearch.com/2021/05/06/understanding-weight-initialization-for-neural-networks/
#

#
# Random
#
class Random:

	@abstractmethod
	def next(self, shape: tuple[int, int]) -> np.ndarray:
		pass

#
# Constant
#
class Constant(Random):

	_value: float

	def __init__(self, value: float):
		self._value = value

	def next(self, shape: tuple[int, int]) -> np.ndarray:
		return np.full(shape, self._value)

#
# Uniform
#
class Uniform(Random):

	_rng: np.random.Generator
	_low: float
	_high: float

	def __init__(self, low: float = 0.0, high: float = 1.0, seed: int = None):
		assert low <= high, "Random::Uniform: `low` must be lower than `high`."

		self._rng = np.random.default_rng(seed)
		self._low = low
		self._high = high

	def next(self, shape: tuple[int, int]) -> np.ndarray:
		return self._rng.uniform(self._low, self._high, size=shape)

#
# Normal
#
class Normal(Random):

	_rng: np.random.Generator
	_mean: float
	_spread: float

	def __init__(self, mean: float = 0.5, spread: float = 0.5, seed: int = None):
		assert spread >= 0, "Random::Normal: `spread` must be non-negative."

		self._rng = np.random.default_rng(seed)
		self._mean = mean
		self._spread = spread

	def next(self, shape: tuple[int, int]) -> np.ndarray:
		return self._rng.normal(self._mean, self._spread, size=shape)

#
# XavierUniform
#
class XavierUniform(Random):

	_rng: np.random.Generator

	def __init__(self, seed: int = None):
		self._rng = np.random.default_rng(seed)

	def next(self, shape: tuple[int, int]) -> np.ndarray:
		limit = np.sqrt(6. / float(shape[0] + shape[1]))
		return self._rng.uniform(-limit, limit, size=shape)

#
# XavierNormal
#
class XavierNormal(Random):

	_rng: np.random.Generator

	def __init__(self, seed: int = None):
		self._rng = np.random.default_rng(seed)

	def next(self, shape: tuple[int, int]) -> np.ndarray:
		limit = np.sqrt(2. / float(shape[0] + shape[1]))
		return self._rng.normal(0.0, limit, size=shape)

#
# HeUniform
#
class HeUniform(Random):

	_rng: np.random.Generator

	def __init__(self, seed: int = None):
		self._rng = np.random.default_rng(seed)

	def next(self, shape: tuple[int, int]) -> np.ndarray:
		limit = np.sqrt(6. / float(shape[0]))
		return self._rng.uniform(-limit, limit, size=shape)

#
# HeNormal
#
class HeNormal(Random):

	_rng: np.random.Generator

	def __init__(self, seed: int = None):
		self._rng = np.random.default_rng(seed)

	def next(self, shape: tuple[int, int]) -> np.ndarray:
		limit = np.sqrt(2. / float(shape[0]))
		return self._rng.normal(0.0, limit, size=shape)
