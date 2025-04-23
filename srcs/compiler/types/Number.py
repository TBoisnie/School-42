from __future__ import annotations

from compiler.interface.SetInterface import SetInterface
from compiler.types.Fraction import Fraction

class Number(SetInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self, val: Fraction) -> None:
		self.value = val

	# - Methods ----------------------------------------------------------------
	def clone(self) -> Number:
		return Number(self.value)

	# - Checkers & Converter ---------------------------------------------------
	def isInt(self) -> bool:
		return self.toFloat() == int(self.toFloat())

	def toFloat(self) -> float:
		return self._value.toFloat()

	def toInt(self) -> int:
		return self._value.toInt()

	# - Getters & Setters ------------------------------------------------------
	@property
	def value(self) -> Fraction:
		return self._value

	@value.setter
	def value(self, val: Fraction) -> None:
		self._value = val.clone()

	# - Overloads --------------------------------------------------------------
	def __add__(self, other: Number) -> Number:
		return Number(self.value + other.value)

	def __sub__(self, other: Number) -> Number:
		return Number(self.value - other.value)

	def __mul__(self, other: Number) -> Number:
		return Number(self.value * other.value)

	def __truediv__(self, other: Number) -> Number:
		return Number(self.value / other.value)

	def __mod__(self, other: Number) -> Number:
		return Number(self.value % other.value)

	def __pow__(self, exp: Number) -> Number:
		return Number(self.value ** exp.value)

	def __neg__(self) -> Number:
		return Number(-self.value)

	def __repr__(self) -> str:
		return f"{self.value}"

	# - Statics ----------------------------------------------------------------
	@staticmethod
	def null() -> Number:
		return Number.fromLiteral(0.0)

	@staticmethod
	def identity() -> Number:
		return Number.fromLiteral(1.0)

	@staticmethod
	def fromLiteral(n: int|float) -> Number:
		return Number(Fraction(n))

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_value: Fraction
