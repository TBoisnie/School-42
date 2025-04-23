from typing import List

class Math:
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Statics ----------------------------------------------------------------
	@staticmethod
	def min(values: List[float|int]) -> float|int:
		assert(len(values) > 0)

		m = values[0]
		for val in values:
			if val < m :
				m = val

		return m

	@staticmethod
	def max(values: List[float|int]) -> float|int:
		assert(len(values) > 0)

		m = values[0]
		for val in values:
			if val > m :
				m = val

		return m

	@staticmethod
	def abs(x: int|float) -> int|float:
		return x if x >= 0 else -x

	@staticmethod
	def floor(x: int|float) -> int:
		return int(x) - (x < 0 and x % 1 != 0)

	@staticmethod
	def ceil(x: int|float) -> int:
		return -Math.floor(-x)

	@staticmethod
	def pow(x: int|float, exp: int) -> float:
		if exp == 0:
			return 1

		power = Math.pow(x, exp // 2)

		if exp % 2 == 0:
			return power * power
		elif exp > 0:
			return x * power * power

		return (power * power) / x

	@staticmethod
	def mod(x: int, y:int) -> int:
		factor = Math.floor(x / y)
		return x - y * factor

	@staticmethod
	def sqrt(n: int|float, accuracy: float = 1e-12) -> float:
		x = n
		y = 1

		while(x - y > accuracy):
			x = (x + y) / 2
			y = n / x

		return x

	@staticmethod
	def gcd(x: int, y: int) -> int:
		while(y):
			x, y = y, x % y
		return int(Math.abs(x))

	@staticmethod
	def primeFactors(x: int) -> List[int]:
		factors : list[int] = []

		factor = 2
		while factor * factor <= x:
			if x % factor:
				factor += 1
			else:
				x //= factor
				factors.append(factor)

		if x > 1:
			factors.append(x)

		return factors
