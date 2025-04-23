from __future__ import annotations
from typing import Generator

class Test:
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Methods ----------------------------------------------------------------
	@staticmethod
	def generate(operands: list[str], operators: list[str]) -> Generator[str, None, None]:
		terms : list[str] = []

		for operand_left in operands:
			for operand_right in operands:
				for operator in operators:
					term = f"({operand_left}) {operator} ({operand_right})"
					terms.append(term)
					yield f"{term} = ?"

		for term_left in terms:
			for term_right in terms:
				for operator in operators:
					yield f"({term_left}) {operator} ({term_right}) = ?"

	@staticmethod
	def defined() -> list[str]:
		return [
			# Subjects
			"8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0 ?",
			"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0 ?",
			"5 * X^0 + 4 * X^1 = 4 * X^0 ?",
			"1 * X^0 = 1 * X^0 ?",
			"8 - 6x + 5.6x^3 = 3 ?",
			"5 + 4x - 9.3x^2 = 1 ?",
			"5 + 4x = 4 ?",
			"1 = 1 ?",
			"8 - 6x + x^3 = x^3 ?",
			"0x^2+1=0 ?",
			"4 + 5 = ?",
			"4 + = 5 ?",
			"4 5 = -1 ?",
			# Specials
			"4 +",
			"f(x) = x + 5.4",
			"a = 2 * 3.1415 * 5",
			"4.5 + f(5) = ?",
			"4.5 + A = ?",
			"M = [[1,2,3];[4,5,6]] + [[6,5,4];[3,2,1]]",
			"C = 5 + i",
			"2 * x^2 + 3 * x - 1 = 0 ?",
			"(2 + a) / 3a = ?",
			"f(f(x))=?",
			# Generals
			"f(x) + 2*x^2 = x^2 ?",
			"2x^2 + 3x = -x^2 - 3 ?", # Priority of Pow: 2x^2 == 2 * (x^2) ; -x^2 == - (x^2)
			"3*(x)^2 + 3x^(1+1) = -(x)^2 - 3 ?",
			"(3 + 4) * (3 + i * 3 - 1) / 3 = ?",
			"(4 - i) * (4 / 2 + 1)i = ?",
			"f(5+3) - f(5+3) = ?",
			"(-x^2*5+4x-3-x) + (2x+4) - x^2*(4-3) + (x-3-2*(4+x+3)*4) - x = 0?", # −6x2−3x−58 = 0
			"((-x^2*5+4x-3-x) + (2x+4) - x^2*(4-3) + (x-3-2*(4+x+3)*4) - x) / 2x = ?",
			"(x*y*z) * (x+2) = ?",
			"x + (-2 - (y)) = ?",
			"y * (x - (-5 ^ (y))) = ?",
			"5 / (i / (y - (-2 % (y)))) = ?",
			"y * (5 + (i * (x + (y)))) = ?",
			"-2 % (y * (5 - (i * (x - (y))))) = ?",
			"-3+x*(42x+4-x)+5x+1-x*(-2-6/(8%3))=?"
		]
