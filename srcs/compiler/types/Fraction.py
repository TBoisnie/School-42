from __future__ import annotations

from compiler.interface.SetInterface import SetInterface
from compiler.types.Error import DivisionByZero
from utilities.Math import Math

class Fraction(SetInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self, num: int|float, denom: int = 1) -> None:
		if not isinstance(num, int):
			while not num.is_integer():
				num = num * 10
				denom = denom * 10
			num = int(num)

		self.num = num
		self.denom = denom

	# - Methods ----------------------------------------------------------------
	def reduce(self) -> Fraction:
		gcd = Math.gcd(self.num, self.denom)

		self.num = self.num // gcd
		self.denom = self.denom // gcd

		return self

	def clone(self) -> Fraction:
		return Fraction(self.num, self.denom)

	# - Checkers & Converters --------------------------------------------------
	# https://www.quora.com/How-can-you-tell-if-a-rational-number-can-be-expressed-in-decimal-form-with-a-finite-number-of-digits
	def isFinite(self) -> bool:
		prime_factors = Math.primeFactors(int(Math.abs(self.clone().reduce().denom)))
		prime_factors_filtered = [ x for x in prime_factors if x != 2 and x != 5 ]
		return len(prime_factors_filtered) == 0

	def isInt(self) -> bool:
		return self.toFloat().is_integer()

	def toFloat(self) -> float:
		return self.num / self.denom

	def toInt(self) -> int:
		return int(self.toFloat())

	# - Getters & Setters ------------------------------------------------------
	@property
	def num(self) -> int:
		return self._numerator

	@num.setter
	def num(self, num: int) -> None:
		self._numerator = num

	@property
	def denom(self) -> int:
		return self._denominator

	@denom.setter
	def denom(self, denom: int) -> None:
		if denom == 0:
			raise DivisionByZero
		self._denominator = denom

	# - Overloads --------------------------------------------------------------
	def __add__(self, other: Fraction) -> Fraction:
		num = self.num * other.denom + other.num * self.denom
		denom = self.denom * other.denom

		return Fraction(num, denom).reduce()

	def __sub__(self, other: Fraction) -> Fraction:
		num = self.num * other.denom - other.num * self.denom
		denom = self.denom * other.denom

		return Fraction(num, denom).reduce()

	def __mul__(self, other: Fraction) -> Fraction:
		num = self.num * other.num
		denom = self.denom * other.denom

		return Fraction(num, denom).reduce()

	def __truediv__(self, other: Fraction) -> Fraction:
		num = self.num * other.denom
		denom = self.denom * other.num

		return Fraction(num, denom).reduce()

	def __pow__(self, exp: Fraction) -> Fraction:
		num = Math.pow(self.num, exp.toInt())
		denom = Math.pow(self.denom, exp.toInt())

		return Fraction(num, int(denom)).reduce()

	def __mod__(self, other: Fraction) -> Fraction:
		num = Math.mod(self.toInt(), other.toInt())

		return Fraction(num)

	def __neg__(self) -> Fraction:
		return Fraction(-self.num, self.denom)

	def __repr__(self) -> str:
		MAX_PRIME_FACTORISABLE = 1_000_000
		return \
			f"{self.num}_{self.denom}" if Math.abs(self.denom) < MAX_PRIME_FACTORISABLE and not self.isFinite() else \
			f"{self.toInt()}" if self.isInt() else \
			f"{self.toFloat():.6g}"

	def __eq__(self, other: Fraction) -> bool:
		return (self.num == other.num and self.denom == other.denom)

	# - Statics ----------------------------------------------------------------
	@staticmethod
	def null() -> Fraction:
		return Fraction(0, 1)

	@staticmethod
	def identity() -> Fraction:
		return Fraction(1, 1)

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_numerator: int
	_denominator: int
