from __future__ import annotations
from typing import cast

from compiler.parser.Node import *

class Optimizer(VisitorInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self) -> None:
		pass

	# - Methods ----------------------------------------------------------------
	def optimize(self, ast: Node) -> StatementNode:
		self._ast = ast

		return cast(StatementNode, self._ast.accept(self))

	# - Interfaces -------------------------------------------------------------
	def visitEquation(self, eq: EquationNode) -> EquationNode:
		eq.left = BinaryOpNode(BinaryOpNode.Type.SUB, eq.left, eq.right)
		eq.right = NumberNode(Number.fromLiteral(0))

		eq.left = cast(ExpressionNode, eq.left.accept(self))

		return eq

	def visitBinaryOp(self, op: BinaryOpNode) -> ExpressionNode:
		op.left = cast(ExpressionNode, op.left.accept(self))
		op.right = cast(ExpressionNode, op.right.accept(self))

		if isinstance(op.left, ValueNode) and isinstance(op.right, ValueNode):
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
		if isinstance(add.right, UnaryOpNode) \
			and add.right.op is UnaryOpNode.Type.NEG:
			# ... + -... == ... - ...
			left = add.left
			right = add.right.value
			op = BinaryOpNode(BinaryOpNode.Type.SUB, left, right)
			return cast(ExpressionNode, op.accept(self))

		if self._getVariableName(add.left) is not None \
			and self._getVariableName(add.right) is None:
			# x + ... == ... + x
			# x^... +... == ... + x^...
			add.left, add.right = add.right, add.left

		if not self._isValueNodeTree(add.left) \
			and self._isValueNodeTree(add.right):
			# ... + n  == n + ...
			add.left, add.right = add.right, add.left

		if isinstance(add.right, BinaryOpNode):
			match add.right.op:
				case BinaryOpNode.Type.ADD:
					if self._isValueNodeTree(add.right.left):
						# ... + ( n + ...) == (... + n) = ...
						left = BinaryOpNode(BinaryOpNode.Type.ADD, add.left, add.right.left)
						right = add.right.right
						op = BinaryOpNode(BinaryOpNode.Type.ADD, left, right)
						return cast(ExpressionNode, op.accept(self))

				case _:
					pass

		if isinstance(add.left, BinaryOpNode):
			match add.left.op:
				case BinaryOpNode.Type.ADD:
					if not self._isValueNodeTree(add.left.right) \
						and self._isValueNodeTree(add.right):
						# (... + ...) + n == (... + n) + ...
						left = BinaryOpNode(BinaryOpNode.Type.ADD, add.left.left, add.right)
						right = add.left.right
						op = BinaryOpNode(BinaryOpNode.Type.ADD, left, right)
						return cast(ExpressionNode, op.accept(self))
				case _:
					pass

		return add

	def _sub(self, sub: BinaryOpNode) -> ExpressionNode:
		return sub

	def _mul(self, mul: BinaryOpNode) -> ExpressionNode:
		if isinstance(mul.left, UnaryOpNode) \
			and isinstance(mul.right, UnaryOpNode) \
			and mul.left.op is UnaryOpNode.Type.NEG \
			and mul.right.op is UnaryOpNode.Type.NEG:
			# -... * -... == ... * ...
			mul.left = mul.left.value
			mul.right = mul.right.value
			return cast(ExpressionNode, mul.accept(self))

		if self._getVariableName(mul.left) is not None \
			and self._getVariableName(mul.right) is None:
			# x * ... == ... * x
			# x^... * ... == ... * x^...
			mul.left, mul.right = mul.right, mul.left

		if isinstance(mul.right, BinaryOpNode):
			match mul.right.op:
				case BinaryOpNode.Type.MUL:
					if not isinstance(mul.left, BinaryOpNode) \
						or mul.left.op is not BinaryOpNode.Type.MUL:
						# ... * (...*...) == (... * ...) * ...
						left = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left, mul.right.left)
						right = mul.right.right
						op = BinaryOpNode(mul.right.op, left, right)
						return cast(ExpressionNode, op.accept(self))

				case BinaryOpNode.Type.ADD|BinaryOpNode.Type.SUB:
					# ... * (... + ...) == ... * ... + ... * ...
					# ... * (... - ...) == ... * ... - ... * ...
					left = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left, mul.right.left)
					right = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left, mul.right.right)
					op = BinaryOpNode(mul.right.op, left, right)
					return cast(ExpressionNode, op.accept(self))

				case _:
					pass

		if isinstance(mul.left, BinaryOpNode):
			match mul.left.op:
				case BinaryOpNode.Type.MUL:
					left_name = self._getVariableName(mul.left.right)
					right_name = self._getVariableName(mul.right)

					if left_name is not None and right_name is not None:
						if left_name == right_name:
							# (... * x) * x == ... * (x * x)
							left = mul.left.left
							right = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left.right, mul.right)
							op = BinaryOpNode(BinaryOpNode.Type.MUL, left, right)
							return cast(ExpressionNode, op.accept(self))

						if left_name > right_name:
							# (... * y) * x == (... * x) * y
							mul.left.right, mul.right = mul.right, mul.left.right
							return cast(ExpressionNode, mul.accept(self))

					if left_name is not None and right_name is None:
						# ( ... * x) * ... == (... * ...) * x
						left = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left.left, mul.right)
						right = mul.left.right
						op = BinaryOpNode(BinaryOpNode.Type.MUL, left, right)
						return cast(ExpressionNode, op.accept(self))

				case BinaryOpNode.Type.ADD|BinaryOpNode.Type.SUB:
					# (... + ...) * ... == ... * ... + ... * ...
					# (... - ...) * ... == ... * ... - ... * ...
					left = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left.left, mul.right)
					right = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left.right, mul.right)
					op = BinaryOpNode(mul.left.op, left, right)
					return cast(ExpressionNode, op.accept(self))

				case _:
					pass

		if isinstance(mul.left, VariableCallNode):
			if isinstance(mul.right, VariableCallNode):
				if mul.left.name == mul.right.name:
					# x * x == x^2
					left = mul.left
					right = NumberNode(Number.fromLiteral(2))
					op = BinaryOpNode(BinaryOpNode.Type.POW, left, right)
					return cast(ExpressionNode, op.accept(self))

				if mul.left.name > mul.right.name:
					# y * x == x * y
					mul.left, mul.right = mul.right, mul.left
					return cast(ExpressionNode, mul.accept(self))

			if isinstance(mul.right, BinaryOpNode) \
				and mul.right.op is BinaryOpNode.Type.POW \
				and isinstance(mul.right.left, VariableCallNode):

				if mul.left.name == mul.right.left.name:
					# x * x^... == x ^ (... + 1)
					left = mul.left
					right = BinaryOpNode(BinaryOpNode.Type.ADD, mul.right.right, NumberNode(Number.identity()))
					op = BinaryOpNode(BinaryOpNode.Type.POW, left, right)
					return cast(ExpressionNode, op.accept(self))

				if mul.left.name > mul.right.left.name:
					# y * x^... == x^... * y
					mul.left, mul.right = mul.right, mul.left
					return cast(ExpressionNode, mul.accept(self))

		if isinstance(mul.left, BinaryOpNode) \
			and mul.left.op is BinaryOpNode.Type.POW \
			and isinstance(mul.left.left, VariableCallNode):

			if isinstance(mul.right, VariableCallNode):
				if mul.left.left.name == mul.right.name:
					# x^... * x == x^(... + 1)
					left = mul.right
					right = BinaryOpNode(BinaryOpNode.Type.ADD, mul.left.right, NumberNode(Number.identity()))
					op = BinaryOpNode(BinaryOpNode.Type.POW, left, right)
					return cast(ExpressionNode, op.accept(self))

				if mul.left.left.name > mul.right.name:
					# y^... * x == x * y^...
					mul.left, mul.right = mul.right, mul.left
					return cast(ExpressionNode, mul.accept(self))

			if isinstance(mul.right, BinaryOpNode) \
				and mul.right.op is BinaryOpNode.Type.POW \
				and isinstance(mul.right.left, VariableCallNode):

				if mul.left.left.name == mul.right.left.name:
					# x^... * x^... == x^(... + ...)
					left = mul.left.left
					right = BinaryOpNode(BinaryOpNode.Type.ADD, mul.left.right, mul.right.right)
					op = BinaryOpNode(BinaryOpNode.Type.POW, left, right)
					return cast(ExpressionNode, op.accept(self))

				if mul.left.left.name > mul.right.left.name:
					# y^... * x^... == x^... * y^...
					mul.left, mul.right = mul.right, mul.left
					return cast(ExpressionNode, mul.accept(self))

		return mul

	def _pow(self, pow: BinaryOpNode) -> ExpressionNode:
		return pow

	def _neg(self, neg: UnaryOpNode) -> ExpressionNode:
		if isinstance(neg.value, UnaryOpNode):
			match neg.value.op:
				case UnaryOpNode.Type.NEG:
					# --x == x
					return cast(ExpressionNode, neg.value.value.accept(self))

		if isinstance(neg.value, BinaryOpNode):
			match neg.value.op:
				case BinaryOpNode.Type.MUL:
					# -(... * ...) == -... * ...
					neg.value.left = UnaryOpNode(UnaryOpNode.Type.NEG, neg.value.left)
					return cast(ExpressionNode, neg.value.accept(self))
				case BinaryOpNode.Type.ADD:
					# -(... + ...) == -... - ...
					neg.value.left = UnaryOpNode(UnaryOpNode.Type.NEG, neg.value.left)
					neg.value.op = BinaryOpNode.Type.SUB
					return cast(ExpressionNode, neg.value.accept(self))
				case BinaryOpNode.Type.SUB:
					# -(... - ...) == -... + ...
					neg.value.left = UnaryOpNode(UnaryOpNode.Type.NEG, neg.value.left)
					neg.value.op = BinaryOpNode.Type.ADD
					return cast(ExpressionNode, neg.value.accept(self))
				case _:
					pass

		if self._getVariableName(neg.value) is not None:
			# -x == -1 * x
			# -x^... == -1 * x^...
			left = UnaryOpNode(UnaryOpNode.Type.NEG, NumberNode(Number.identity()))
			right = neg.value
			return cast(ExpressionNode, BinaryOpNode(BinaryOpNode.Type.MUL, left, right).accept(self))

		return neg

	# - Checkers & Converters --------------------------------------------------
	def _getVariableName(self, expr: ExpressionNode) -> str|None:
		# x
		if isinstance(expr, VariableCallNode):
			return expr.name

		# x ^ ...
		if isinstance(expr, BinaryOpNode) \
			and expr.op is BinaryOpNode.Type.POW \
			and isinstance(expr.left, VariableCallNode):

			return expr.left.name

		return None

	def _isValueNodeTree(self, root: ExpressionNode) -> bool:
		if isinstance(root, BinaryOpNode):
			left = self._isValueNodeTree(root.left)
			right = self._isValueNodeTree(root.right)
			return left and right

		if isinstance(root, UnaryOpNode):
			value = self._isValueNodeTree(root.value)
			return value

		if isinstance(root, ValueNode):
			return True

		return False
