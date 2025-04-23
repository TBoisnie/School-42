from __future__ import annotations
from typing import cast

from compiler.interpreter.Error import *
from compiler.parser.Node import *

class Interpreter(VisitorInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self) -> None:
		pass

	# - Methods ----------------------------------------------------------------
	def run(self, ast: Node) -> StatementNode:
		self._ast = ast

		return cast(StatementNode, ast.accept(self))

	# - Interfaces -------------------------------------------------------------
	def visitEquation(self, eq: EquationNode) -> EquationNode:
		eq.left = cast(ExpressionNode, eq.left.accept(self))
		return eq

	def visitBinaryOp(self, op: BinaryOpNode) -> ExpressionNode:
		op.left = cast(ExpressionNode, op.left.accept(self))
		op.right = cast(ExpressionNode, op.right.accept(self))

		if not isinstance(op.left, ValueNode) or not isinstance(op.right, ValueNode):
			return op

		match op.op:
			case BinaryOpNode.Type.ADD:
				return self._add(op)
			case BinaryOpNode.Type.SUB:
				return self._sub(op)
			case BinaryOpNode.Type.MUL:
				return self._mul(op)
			case BinaryOpNode.Type.POW:
				return self._pow(op)

	def visitUnaryOp(self, op: UnaryOpNode) -> ExpressionNode:
		op.value = cast(ExpressionNode, op.value.accept(self))

		if not isinstance(op.value, ValueNode):
			return op

		match op.op:
			case UnaryOpNode.Type.NEG:
				return self._neg(op)

	def visitVariableCall(self, var_call: VariableCallNode) -> ExpressionNode:
		return var_call

	def visitNumber(self, number: NumberNode) -> NumberNode:
		return number

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_ast: Node

	# - Methods ----------------------------------------------------------------
	def _add(self, add: BinaryOpNode) -> ExpressionNode:
		# Number + Any
		if isinstance(add.left, NumberNode):
			# Number + Number
			if isinstance(add.right, NumberNode):
				return NumberNode(add.left.value + add.right.value)

		raise UnsupportedOperator(add.op, f"Can't add {add.left.__class__.__name__} to {add.right.__class__.__name__}")

	def _sub(self, sub: BinaryOpNode) -> ExpressionNode:
		# Number - Any
		if isinstance(sub.left, NumberNode):
			# Number - Number
			if isinstance(sub.right, NumberNode):
				return NumberNode(sub.left.value - sub.right.value)

		raise UnsupportedOperator(sub.op, f"Can't substract {sub.left.__class__.__name__} by {sub.left.__class__.__name__}.")

	def _mul(self, mul: BinaryOpNode) -> ExpressionNode:
		# Number * Any
		if isinstance(mul.left, NumberNode):
			# Number * Number
			if isinstance(mul.right, NumberNode):
				return NumberNode(mul.left.value * mul.right.value)

		raise UnsupportedOperator(mul.op, f"Can't multiply {mul.left.__class__.__name__} by {mul.right.__class__.__name__}.")

	def _pow(self, pow: BinaryOpNode) -> ExpressionNode:
		# Any ^ Number
		if not isinstance(pow.right, NumberNode) or not pow.right.value.isInt() or pow.right.value.toInt() < 0:
			raise UnsupportedOperator(pow.op, f"Exponent must be a positive integer.")

		# Number ^ Number
		if isinstance(pow.left, NumberNode):
			return NumberNode(pow.left.value ** pow.right.value)

		raise UnsupportedOperator(pow.op, f"Can't pow with {pow.left.__class__.__name__} base.")

	def _neg(self, neg: UnaryOpNode) -> ExpressionNode:
		# Number
		if isinstance(neg.value, NumberNode):
			return NumberNode(-neg.value.value)

		raise UnsupportedOperator(neg.op, f"Can't negate {neg.value.__class__.__name__}.")

	def _findEquationUnknown(self, expr: ExpressionNode) -> str|None:
		if isinstance(expr, VariableCallNode):
			return expr.name

		if isinstance(expr, BinaryOpNode):
			unknown = self._findEquationUnknown(expr.left)

			if unknown is None:
				return self._findEquationUnknown(expr.right)

			return unknown

		if isinstance(expr, UnaryOpNode):
			return self._findEquationUnknown(expr.value)

		return None
