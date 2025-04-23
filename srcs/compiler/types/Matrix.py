from __future__ import annotations

from compiler.interface.SetInterface import SetInterface
from compiler.types.Error import IndexOutOfBound, UnsupportedOperator
from compiler.types.Number import Number

class Matrix(SetInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self, rows: int, cols: int, default: Number = Number.null()) -> None:
		self._rows = rows
		self._cols = cols

		self.fill(default)

	# - Methods ----------------------------------------------------------------
	def fill(self, value: Number):
		self._values = [ [ value for _ in range(self.cols) ] for _ in range(self.rows) ]
		return self

	def clone(self) -> Matrix:
		mat = Matrix(self.rows, self.cols)
		mat._values = [ [ self.get(i+1, j+1).clone() for j in range(self.cols) ] for i in range(self.rows) ]
		return mat

	# - Checkers & Converters --------------------------------------------------
	def isSquare(self) -> bool:
		return self.rows == self.cols

	# - Getters & Setters ------------------------------------------------------
	@property
	def rows(self) -> int:
		return self._rows

	@property
	def cols(self) -> int:
		return self._cols

	def get(self, row: int, col: int) -> Number:
		self._checkBounds(row, col)
		return self._values[row-1][col-1]

	def set(self, row: int, col: int, value: Number):
		self._checkBounds(row, col)
		self._values[row-1][col-1] = value
		return self

	# - Overloads --------------------------------------------------------------
	def __add__(self, other: Matrix) -> Matrix:
		self._checkSizeMatch(other, "Add")

		mat = Matrix(self.rows, self.cols)

		for i in range(self.rows):
			for j in range(self.cols):
				mat.set(i+1, j+1, self.get(i+1, j+1) + other.get(i+1, j+1))

		return mat

	def __sub__(self, other: Matrix) -> Matrix:
		self._checkSizeMatch(other, "Sub")

		mat = Matrix(self.rows, self.cols)

		for i in range(self.rows):
			for j in range(self.cols):
				mat.set(i+1, j+1, self.get(i+1, j+1) - other.get(i+1, j+1))

		return mat

	def __mul__(self, other: Matrix) -> Matrix:
		self._checkSizeMatch(other, "Mul")

		mat = Matrix(self.rows, self.cols)

		for i in range(self.rows):
			for j in range(self.cols):
				mat.set(i+1, j+1, self.get(i+1, j+1) * other.get(i+1, j+1))

		return mat

	def __matmul__(self, other: Matrix) -> Matrix:
		if self.cols != other.rows:
			raise UnsupportedOperator(f"MulMat: Sizes doesn't match ({self.rows}, {self.cols}) and ({other.rows}, {other.cols}).")

		mat = Matrix(self.rows, self.cols)

		for i in range(self.rows):
			for j in range(self.cols):
				for k in range(other.rows):
					mat.set(i+1, j+1, mat.get(i+1, j+1) + self.get(i+1, k+1) * other.get(k+1, j+1))

		return mat

	def __truediv__(self, other: Number) -> Matrix:
		raise UnsupportedOperator("Div: Can't divide a Matrix.")

	def __pow__(self, exp: Number) -> Matrix:
		if self.rows != self.cols:
			raise UnsupportedOperator("Pow: Matrix must be square.")
		if not exp.isInt() or exp.toInt() < 0:
			raise UnsupportedOperator("Pow: Exponent must be ant Int >= 0.")

		mat = Matrix.identity(self.rows)

		exponent = exp.toInt()
		while exponent > 0:
			mat = mat @ self
			exponent -= 1

		return mat

	def __neg__(self) -> Matrix:
		return self * Matrix(self.rows, self.cols, -Number.identity())

	def __repr__(self) -> str:
		return f"{self._values}"

	def __eq__(self, other: Matrix) -> bool:
		if self.rows != other.rows or self._cols != other.cols:
			return False

		for i in range(self.rows):
			for j in range(self.cols):
				if self.get(i+1, j+1) != other.get(i+1, j+1):
					return False

		return True

	# - Statics ----------------------------------------------------------------
	@staticmethod
	def null(rows: int = 3, cols: int = 3) -> Matrix:
		return Matrix(rows, cols, Number.null())

	@staticmethod
	def identity(size: int = 3) -> Matrix:
		mat = Matrix.null(size, size)

		for i in range(mat.rows):
			mat.set(i+1, i+1, Number.identity())

		return mat

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_rows: int
	_cols: int

	_values: list[list[Number]]

	# - Checkers & Converters --------------------------------------------------
	def _checkSizeMatch(self, other: Matrix, op: str) -> None:
		if self.cols != other.cols or self.rows != other.rows:
			raise UnsupportedOperator(f"{op}: Matrices have different sizes ({self.rows},{self.cols}) and ({other.rows},{other.cols}).")

	def _checkBounds(self, row: int, col: int) -> None:
		if row <= 0 or row > self.rows:
			raise IndexOutOfBound(f"Row index ({row}) must be between {1} and {self.rows}.")
		if col <= 0 or col > self.cols:
			raise IndexOutOfBound(f"Col index ({col}) must be between {1} and {self.cols}.")
