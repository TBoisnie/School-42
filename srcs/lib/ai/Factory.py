from __future__ import annotations
from abc import ABC, abstractmethod

import numpy as np

from lib.fmt.Json import Json
from .Model import Model, Perceptron
from .Layer import Layer, Dense
from .Activation import Activation, Identity, ReLU, TanH, Sigmoid, SoftMax
from .Optimizer import Optimizer, StochasticGradientDescent, AdaptiveGradient, Momentum, NesterovMomentum, RootMeanSquarePropagation
from .Loss import Loss, MeanSquaredError, MeanAbsoluteError, CategoricalCrossEntropy, BinaryCrossEntropy

#
# Factory
#
class Factory(ABC):

	@classmethod
	@abstractmethod
	def create(cls, type: str, args: dict, state: dict):
		pass

	@staticmethod
	@abstractmethod
	def get_accepted_types(cls) -> list:
		pass

	@staticmethod
	@abstractmethod
	def from_json(cls, json: Json):
		pass

#
# BaseFactory
#
class BaseFactory(Factory):

	@classmethod
	def create(cls, type: str, args: dict = {}, state: dict = {}):
		for c in cls.get_accepted_types():
			if type == c.__name__:
				instance = c(**args)

				for k, v in state.items():
					getattr(instance, f"set_{k}")(v)

				return instance

		raise ValueError(f"AI::Factory::Base::Create: Unsupported type `{type}`.")

#
# ModelFactory
#
class ModelFactory(BaseFactory):

	@staticmethod
	def get_accepted_types() -> list[Model]:
		return [
			Perceptron,
		]

	@staticmethod
	def from_json(json: Json) -> Model:
		type = json['type']
		args = {}

		if 'args' in json:
			if 'optimizer' in json['args']:
				args['optimizer'] = OptimizerFactory.from_json(json['args']['optimizer'])
			if 'loss' in json['args']:
				args['loss'] = LossFactory.from_json(json['args']['loss'])
			if 'layers' in json['args']:
				args['layers'] = [ LayerFactory.from_json(json_layer) for json_layer in json['args']['layers'] ]

		return ModelFactory.create(type, args)

#
# OptimizerFactory
#
class OptimizerFactory(BaseFactory):

	@staticmethod
	def get_accepted_types() -> list[Optimizer]:
		return [
			StochasticGradientDescent,
			AdaptiveGradient,
			Momentum,
			NesterovMomentum,
			RootMeanSquarePropagation,
		]

	@staticmethod
	def from_json(json: Json) -> Optimizer:
		return OptimizerFactory.create(json['type'], json['args'])

#
# LossFactory
#
class LossFactory(BaseFactory):

	@staticmethod
	def get_accepted_types() -> list[Loss]:
		return [
			BinaryCrossEntropy,
			CategoricalCrossEntropy,
		]

	@staticmethod
	def from_json(json: Json) -> Loss:
		return LossFactory.create(json['type'], json['args'])

#
# LayerFactory
#
class LayerFactory(BaseFactory):

	@staticmethod
	def get_accepted_types() -> list[Layer]:
		return [
			Dense,
		]

	@staticmethod
	def from_json(json: Json) -> Layer:
		type = json['type']
		args = {}
		state = {}

		if 'shape' in json['args']:
			args['shape'] = json['args']['shape']
		if 'activation' in json['args']:
			args['activation'] = ActivationFactory.from_json(json['args']['activation'])

		if 'weights' in json['state']:
			state['weights'] = np.array(json['state']['weights'])
		if 'biases' in json['state']:
			state['biases'] = np.array(json['state']['biases'])

		return LayerFactory.create(type, args, state)

#
# ActivationFactory
#
class ActivationFactory(BaseFactory):

	@staticmethod
	def get_accepted_types():
		return [
			Identity,
			ReLU,
			TanH,
			Sigmoid,
			SoftMax,
		]

	@staticmethod
	def from_json(json: Json) -> Activation:
		return ActivationFactory.create(json['type'])
