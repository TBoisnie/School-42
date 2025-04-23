from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Any

from compiler.parser.Node import *

class VisitorInterface(ABC):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Methods ----------------------------------------------------------------
	@abstractmethod
	def visitNumber(self, number: NumberNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitBinaryOp(self, op: BinaryOpNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitUnaryOp(self, op: UnaryOpNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitVariableCall(self, var_call: VariableCallNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitEquation(self, eq: EquationNode) -> Any:
		raise NotImplementedError

class VisitableInterface(ABC):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Methods ----------------------------------------------------------------
	@abstractmethod
	def accept(self, vtor: VisitorInterface) -> Node:
		raise NotImplementedError
