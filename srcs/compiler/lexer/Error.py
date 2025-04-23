class LexerError(Exception):
	def __init__(self, message: str):
		super().__init__(f"Lexer::{message}")

class InvalidCharacter(LexerError):
	def __init__(self, value: str):
		super().__init__(f"InvalidCharacter: '{value}'.")

class InvalidNumber(LexerError):
	def __init__(self, value: str, info: str = ""):
		super().__init__(f"InvalidNumber: '{value}'{ f' ({info})' if info else ''}.")
