from __future__ import annotations

from compiler.interface.SetInterface import SetInterface
from compiler.types.Fraction import Fraction
from compiler.types.Number import Number

class Complex(SetInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self, re: Fraction, im: Fraction):
		self.re = re
		self.im = im

	# - Methods ----------------------------------------------------------------
	def conjugate(self) -> Complex:
		return Complex(self.re, -self.im)

	def clone(self) -> Complex:
		return Complex(self.re, self.im)

	# - Checkers & Converters --------------------------------------------------
	def isReal(self) -> bool:
		return self.im.num == 0

	# - Getters & Setters ------------------------------------------------------
	@property
	def re(self) -> Fraction:
		return self._real

	@re.setter
	def re(self, re: Fraction):
		self._real = re.clone()

	@property
	def im(self) -> Fraction:
		return self._imaginary

	@im.setter
	def im(self, im: Fraction):
		self._imaginary = im.clone()

	# - Overloads --------------------------------------------------------------
	def __add__(self, other: Complex) -> Complex:
		re = self.re + other.re
		im = self.im + other.im

		return Complex(re, im)

	def __sub__(self, other: Complex) -> Complex:
		re = self.re - other.re
		im = self.im - other.im

		return Complex(re, im)

	def __mul__(self, other: Complex) -> Complex:
		re = self.re * other.re - self.im * other.im
		im = self.re * other.im + self.im * other.re

		return Complex(re, im)

	def __truediv__(self, other: Complex) -> Complex:
		re = self.re * other.re + self.im * other.im
		im = self.im * other.re - self.re * other.im

		denom = other.re * other.re + other.im * other.im

		return Complex(re / denom, im / denom)

	def __pow__(self, exp: Number) -> Complex:
		result = Complex.identity()

		for _ in range(exp.toInt()):
			result = result * self

		return result

	def __neg__(self) -> Complex:
		return Complex(-self.re, -self.im)

	def __repr__(self) -> str:
		re = self.re.toFloat()
		im = self.im.toFloat()

		re_str = f"{ self.re }" if re != 0.0 else f""
		im_str = f"i" if im == 1.0 else f"" if im == 0.0 else f"{ self.im }i"

		sign_str = f"+" if len(re_str) > 0 and len(im_str) > 0 and im > 0.0 else f""

		return f"{ re_str }{ sign_str }{ im_str }"

	# - Statics ----------------------------------------------------------------
	@staticmethod
	def null():
		return Complex.fromLiteral(0, 0)

	@staticmethod
	def identity():
		return Complex.fromLiteral(1, 0)

	@staticmethod
	def fromLiteral(re: int|float, im: int|float) -> Complex:
		return Complex(Fraction(re), Fraction(im))

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_real: Fraction
	_imaginary: Fraction
