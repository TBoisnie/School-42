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
	def visitMatrix(self, matrix: MatrixNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitComplex(self, complex: ComplexNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitBinaryOp(self, op: BinaryOpNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitUnaryOp(self, op: UnaryOpNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitVariableDef(self, var_def: VariableDefNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitVariableCall(self, var_call: VariableCallNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitFunctionDef(self, fun_def: FunctionDefNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitFunctionCall(self, fun_call: FunctionCallNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitEquation(self, eq: EquationNode) -> Any:
		raise NotImplementedError

	@abstractmethod
	def visitEval(self, eval: EvalNode) -> Any:
		raise NotImplementedError


class VisitableInterface(ABC):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Methods ----------------------------------------------------------------
	@abstractmethod
	def accept(self, vtor: VisitorInterface) -> Node:
		raise NotImplementedError
