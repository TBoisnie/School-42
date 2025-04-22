from functools import singledispatchmethod

from lib.fmt.Json import Json
from .Model import Perceptron
from .Optimizer import StochasticGradientDescent, Momentum, NesterovMomentum, AdaptiveGradient, RootMeanSquarePropagation
from .Layer import Dense
from .Activation import Activation
from .Loss import MeanSquaredError, MeanAbsoluteError, CategoricalCrossEntropy, BinaryCrossEntropy


#
# Serializer
#
class Serializer:

	def __init__(self):
		pass

	# Serialize
	@singledispatchmethod
	def serialize(self, _) -> Json:
		raise TypeError(f"AI::Serializer::Serialize: Unsupported type {_.__class__.__name__}.")

	@serialize.register
	def _(self, model: Perceptron) -> Json:
		return {
			'type': model.__class__.__name__,
			'args': {
				'layers': [ self.serialize(layer) for layer in model._layers ],
				'optimizer': self.serialize(model._optimizer),
				'loss': self.serialize(model._loss),
			}
		}

	@serialize.register
	def _(self, optimizer: StochasticGradientDescent) -> Json:
		return {
			'type': optimizer.__class__.__name__,
			'args': {
				'learning_rate': optimizer._learning_rate,
			},
		}

	@serialize.register
	def _(self, optimizer: Momentum) -> Json:
		return {
			'type': optimizer.__class__.__name__,
			'args': {
				'learning_rate': optimizer._learning_rate,
				'momentum': optimizer._momentum,
			},
		}

	@serialize.register
	def _(self, optimizer: NesterovMomentum) -> Json:
		return {
			'type': optimizer.__class__.__name__,
			'args': {
				'learning_rate': optimizer._learning_rate,
				'momentum': optimizer._momentum,
			},
		}

	@serialize.register
	def _(self, optimizer: AdaptiveGradient) -> Json:
		return {
			'type': optimizer.__class__.__name__,
			'args': {
				'learning_rate': optimizer._learning_rate,
				'epsilon': optimizer._epsilon,
			},
		}

	@serialize.register
	def _(self, optimizer: RootMeanSquarePropagation) -> Json:
		return {
			'type': optimizer.__class__.__name__,
			'args': {
				'learning_rate': optimizer._learning_rate,
				'decay_rate': optimizer._decay_rate,
				'epsilon': optimizer._epsilon,
			},
		}

	@serialize.register
	def _(self, layer: Dense) -> Json:
		return {
			'type': layer.__class__.__name__,
			'args': {
				'shape': layer._weights.shape,
				'activation': self.serialize(layer._activation),
			},
			'state': {
				'weights': layer._weights.tolist(),
				'biases': layer._biases.tolist(),
			},
		}

	@serialize.register
	def _(self, activation: Activation) -> Json:
		return {
			'type': activation.__class__.__name__,
		}

	@serialize.register
	def _(self, loss: MeanSquaredError) -> Json:
		return {
			'type': loss.__class__.__name__,
		}

	@serialize.register
	def _(self, loss: MeanAbsoluteError) -> Json:
		return {
			'type': loss.__class__.__name__,
		}

	@serialize.register
	def _(self, loss: CategoricalCrossEntropy) -> Json:
		return {
			'type': loss.__class__.__name__,
			'args': {
				'epsilon': loss._epsilon,
			},
		}

	@serialize.register
	def _(self, loss: BinaryCrossEntropy) -> Json:
		return {
			'type': loss.__class__.__name__,
			'args': {
				'epsilon': loss._epsilon,
			},
		}
