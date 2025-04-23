from typing import List

class Math:
	# ==========================================================================
	# Public
	# ==========================================================================
	PI: float = 3.14159265358979323846264338327950288419716939937510582097494459
	E : float = 2.71828182845904523536028747135266249775724709369995957496696762

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

		power = Math.pow(x, Math.floor(exp / 2))

		if Math.mod(exp, 2) == 0:
			return power * power
		elif exp > 0:
			return x * power * power

		return (power * power) / x

	@staticmethod
	def mod(x: int, y:int) -> int:
		factor = Math.floor(x / y)
		return x - y * factor

	@staticmethod
	def rad(deg: float) -> float:
		return deg * (Math.PI / 180)

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
			x, y = y, Math.mod(x, y)
		return int(Math.abs(x))

	@staticmethod
	def primeFactors(x: int) -> List[int]:
		assert(x > 0)

		factors : list[int] = []

		factor = 2
		while factor * factor <= x:
			if Math.mod(x, factor):
				factor += 1
			else:
				x = Math.floor(x / factor)
				factors.append(factor)

		if x > 1:
			factors.append(x)

		return factors
