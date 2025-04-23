class MathError(Exception):
	def __init__(self, message: str) -> None:
		super().__init__(f"Math::{message}")

class DivisionByZero(MathError):
	def __init__(self) -> None:
		super().__init__(f"DivisionByZero")

class UnsupportedOperator(MathError):
	def __init__(self, info: str) -> None:
		super().__init__(f"UnsupportedOperator::{info}")
