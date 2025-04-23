from __future__ import annotations
from typing import List

from compiler.interpreter.Error import *
from compiler.parser.Node import *
from compiler.types.Complex import Complex
from compiler.types.Number import Number
from utilities.Math import Math

class EquationSolver(VisitorInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self, ast: EquationNode) -> None:
		self._terms = {}
		self._is_sub = False
		self._delta = None
		self._unknown_name = ''

		ast.accept(self)

	# - Methods ----------------------------------------------------------------
	def solve(self) -> List[Number|Complex]|None:
		if self.degree == 2:
			return self._solveQuadratic()
		if self.degree == 1:
			return self._solveLinear()
		if self.degree == 0:
			return self._solveEquality()
		return None

	def reduceForm(self) -> str:
		terms = f""

		for exponent, base in dict(sorted(self._terms.items(), reverse=True)).items():
			if exponent == 0:
				term = f"{base}"
			else:
				sign_str = f"" if base.toFloat() >= 0.0 else f"-"
				base_str = f"{ base }"      if Math.abs(base.toFloat()) != 1.0 else sign_str
				exp_str  = f"^{ exponent }" if exponent != 1                   else f""

				term = f"{base_str}{self._unknown_name}{exp_str}"

			if len(terms) != 0 and base.toFloat() >= 0.0:
				terms = f"{terms}+"

			terms = f"{terms}{term}"

		return f"{terms} = 0"

	# - Getters & Setters ------------------------------------------------------
	@property
	def degree(self) -> int:
		exponents: List[int|float] = [ 0.0 ] + [ exp for exp, factor in self._terms.items() if factor.toFloat() != 0.0 ]
		return int(Math.max(exponents))

	@property
	def delta(self) -> Number|None:
		return self._delta

	# - Interfaces -------------------------------------------------------------
	def visitEquation(self, eq: EquationNode) -> None:
		# [ n * X^m ]+ = 0
		eq.left.accept(self)

	def visitBinaryOp(self, op: BinaryOpNode) -> None:
		if op.op is BinaryOpNode.Type.SUB:
			op.left.accept(self)
			self._is_sub = not self._is_sub
			op.right.accept(self)
			self._is_sub = not self._is_sub
			return

		if op.op is BinaryOpNode.Type.ADD:
			op.left.accept(self)
			op.right.accept(self)
			return

		if op.op is BinaryOpNode.Type.MUL:
			if not isinstance(op.left, NumberNode):
				raise InvalidEquationFormat(f"InvalidTerm: Factor must be a number.")

			factor = -op.left.value if self._is_sub else op.left.value
			exponent = self.getUnknownExponent(op.right)

			self._updateTerms(factor, exponent)
			return

		if op.op is BinaryOpNode.Type.POW:
			exponent = self.getUnknownExponent(op)
			factor = -Number.identity() if self._is_sub else Number.identity()

			self._updateTerms(factor, exponent)
			return

		raise InvalidEquationFormat(f"InvalidOperator: {op.op.name}.")

	def visitVariableCall(self, var_call: VariableCallNode) -> None:
		exponent = self.getUnknownExponent(var_call)
		factor = -Number.identity() if self._is_sub else Number.identity()

		self._updateTerms(factor, exponent)

	def visitNumber(self, number: NumberNode) -> None:
		factor = -number.value if self._is_sub else number.value
		self._updateTerms(factor, Number.null())

	def visitUnaryOp(self, op: UnaryOpNode) -> None:
		raise InvalidEquationFormat(f"InvalidOperator: {op.op.name}.")

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_terms: dict[int, Number]
	_delta: Number|None
	_is_sub: bool
	_unknown_name: str

	# - Methods ----------------------------------------------------------------
	def _solveQuadratic(self) -> List[Number|Complex]|None:
		# a * X^2 + b * X + c = 0

		a = self._terms.get(2)
		b = self._terms.get(1)
		c = self._terms.get(0)

		a = Number.null() if a is None else a
		b = Number.null() if b is None else b
		c = Number.null() if c is None else c

		if a.toFloat() == 0.0:
			return self._solveLinear()

		self._delta = delta = b ** Number.fromLiteral(2) - Number.fromLiteral(4) * a * c

		num = -b
		denom = Number.fromLiteral(2) * a

		# 1 Solution
		if delta.toFloat() == 0.0:
			return [ num / denom ]

		# 2 Solutions
		is_delta_negative = delta.toFloat() < 0.0

		delta = -delta if is_delta_negative else delta
		sqrt = Number.fromLiteral(Math.sqrt(delta.toFloat()))

		if is_delta_negative:
			zero = Number.null().value

			sqrt = Complex(zero, sqrt.value)
			num = Complex(num.value, zero)
			denom = Complex(denom.value, zero)

			return [ (num - sqrt) / denom, (num + sqrt) / denom ]

		return [ (num - sqrt) / denom, (num + sqrt) / denom ]

	def _solveLinear(self) -> List[Number|Complex]|None:
		# a * X + b = 0

		a = self._terms.get(1)
		b = self._terms.get(0)

		a = Number.null() if a is None else a
		b = Number.null() if b is None else b

		if a.toFloat() == 0.0:
			if b.toFloat() == 0.0:
				return [] # Empty means any value from |R
			return None

		return [ -b / a ]

	def _solveEquality(self) -> List[Number|Complex]|None:
		# a = 0

		a = self._terms.get(0)
		a = Number.null() if a is None else a

		if a.toFloat() == 0.0:
			return [ a ] # True

		return [] # False

	def _updateTerms(self, factor: Number, exponent: Number) -> None:
		if self._terms.get(exponent.toInt()) is None:
			self._terms[exponent.toInt()] = Number.null()

		self._terms[exponent.toInt()] += factor

	def getUnknownExponent(self, expr: ExpressionNode) -> Number:
		# x
		if isinstance(expr, VariableCallNode):
			if self._unknown_name != '' and self._unknown_name != expr.name:
				raise InvalidEquationFormat(f"InvalidTerm: Unknown variable ({ expr.name }).")
			self._unknown_name = expr.name
			return Number.identity()

		# x ^ n
		if not isinstance(expr, BinaryOpNode) \
			or not expr.op is BinaryOpNode.Type.POW \
			or not isinstance(expr.left, VariableCallNode) \
			or not isinstance(expr.right, NumberNode):

			raise InvalidEquationFormat(f"InvalidTerm: Unknown must be in form 'X^n' or 'X', where 'X' is the unknown, and 'n' a number.")

		if not expr.right.value.isInt() \
			or expr.right.value.toInt() < 0:

			raise InvalidEquationFormat(f"InvalidTerm: Exponent must be a positive integer.")

		if self._unknown_name != '' and self._unknown_name != expr.left.name:
			raise InvalidEquationFormat(f"InvalidTerm: Unknown variable ({ expr.left.name }).")

		self._unknown_name = expr.left.name

		return expr.right.value
