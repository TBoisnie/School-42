from typing import Set

from compiler.lexer.Token import *
from compiler.parser.Node import *

class ParserError(Exception):
	def __init__(self, message: str):
		super().__init__(f"Parser::{message}")

class InvalidSyntax(ParserError):
	def __init__(self, got: Token|None, expected: Token.Type|Set[Token.Type]):
		if isinstance(expected, Token.Type):
			expected_str = f"{ expected.name }"
		else:
			expected_str = f"{ ' | '.join([ t.name for t in expected ]) }"

		super().__init__(f"InvalidSyntax: Unexpected '{got}', expected '{expected_str}'.")
