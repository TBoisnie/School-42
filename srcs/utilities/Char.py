from __future__ import annotations

class Char:
	# Spaces
	SPACE = " \t" # \n\v\f\r
	# Alphabetics
	ALPHA = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
	# Numerics
	DIGIT = "0123456789"
	# Groups
	PAREN_L = '('
	PAREN_R = ')'
	BRACK_L = '['
	BRACK_R = ']'
	# Operators
	ADD   = '+'
	SUB   = '-'
	MUL   = '*'
	DIV   = '/'
	MOD   = '%'
	POW   = '^'
	EQUAL = '='
	# Punctuations
	DOT       = '.'
	COMMA     = ','
	SEMICOLON = ';'
	QUESTION  = '?'

	@staticmethod
	def match(chr: str|None, type: str) -> bool:
		return chr is not None and chr in type
