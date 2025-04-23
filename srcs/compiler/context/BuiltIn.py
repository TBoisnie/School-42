from __future__ import annotations
from typing import Tuple

from compiler.types.Complex import Complex
from compiler.types.Number import Number
from compiler.types.Matrix import Matrix
from utilities.Math import Math

class BuiltIn:
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Methods ----------------------------------------------------------------
	@staticmethod
	def getVariablesList() -> Tuple[str, ...]:
		return ('i', 'e', 'pi')

	@staticmethod
	def getFunctionsList() -> Tuple[str, ...]:
		return ('abs', 'sqrt', 'floor', 'ceil', 'rad', 'trace', 'transpose')

	# - Variables --------------------------------------------------------------
	I = Complex.fromLiteral(0, 1)
	E = Number.fromLiteral(Math.E)
	PI = Number.fromLiteral(Math.PI)

	# - Functions --------------------------------------------------------------
	@staticmethod
	def abs(n: Number|Complex) -> Number:
		if isinstance(n, Complex):
			norm = Math.sqrt(Math.pow(n.re.toFloat(), 2) + Math.pow(n.im.toFloat(), 2))
			return Number.fromLiteral(Math.abs(norm))
		return Number.fromLiteral(Math.abs(n.toFloat()))

	@staticmethod
	def sqrt(n: Number) -> Number:
		return Number.fromLiteral(Math.sqrt(n.toFloat()))

	@staticmethod
	def floor(n: Number) -> Number:
		return Number.fromLiteral(Math.floor(n.toFloat()))

	@staticmethod
	def ceil(n: Number) -> Number:
		return Number.fromLiteral(Math.ceil(n.toFloat()))

	@staticmethod
	def rad(n: Number) -> Number:
		return Number.fromLiteral(Math.rad(n.toFloat()))

	@staticmethod
	def trace(m: Matrix) -> Number:
		tr = Number.identity()

		for i in range(1, m.rows+1):
			tr *= m.get(i,i)

		return tr

	@staticmethod
	def transpose(m: Matrix) -> Matrix:
		tr = Matrix(m.cols, m.rows)

		for i in range(1, m.rows+1):
			for j in range(1, m.cols+1):
				tr.set(j, i, m.get(i,j))

		return tr
