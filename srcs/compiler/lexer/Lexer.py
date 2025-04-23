from typing import Iterable

from compiler.lexer.Error import InvalidCharacter, InvalidNumber
from compiler.lexer.Token import Token
from utilities.Char import Char
from utilities.Pickator import Pickator

class Lexer(Iterable[Token]):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self):
		self._source_pkt = Pickator("")
		self._has_reached_end = False

	# - Methods ----------------------------------------------------------------
	def tokenize(self, src_str: str):
		self._source_pkt = Pickator(src_str)
		self._has_reached_end = False
		return self

	# - Overloads --------------------------------------------------------------
	def __iter__(self):
		return self

	def __next__(self) -> Token:
		while self._current_chr is not None:
			# Ignore
			if Char.match(self._current_chr, Char.SPACE):
				self._next()
			# Identifier
			elif Char.match(self._current_chr, Char.ALPHA):
				return self._generateIdentifier()
			# Number
			elif Char.match(self._current_chr, Char.DOT) or Char.match(self._current_chr, Char.DIGIT):
				return self._generateNumber()
			# Atom
			else:
				return self._generateAtom()

		if not self._has_reached_end:
			self._has_reached_end = True
			return Token(Token.Type.END)

		raise StopIteration

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_source_itr: Pickator[str]
	_has_reached_end: bool

	# - Methods ----------------------------------------------------------------
	def _generateAtom(self) -> Token:
		assert(self._current_chr is not None)

		token_type = \
			Token.Type.ADD   if self._current_chr == Char.ADD else \
			Token.Type.SUB   if self._current_chr == Char.SUB else \
			Token.Type.MUL   if self._current_chr == Char.MUL else \
			Token.Type.POW   if self._current_chr == Char.POW else \
			Token.Type.EQUAL if self._current_chr == Char.EQUAL else \
			Token.Type.INVALID

		if token_type is Token.Type.INVALID:
			raise InvalidCharacter(self._current_chr)

		self._next()

		return Token(token_type)

	def _generateIdentifier(self) -> Token:
		identifier = ""

		while self._current_chr is not None:
			if not Char.match(self._current_chr, Char.ALPHA):
				break

			identifier += self._current_chr
			self._next()

		return Token(Token.Type.IDENTIFIER, identifier)

	def _generateNumber(self) -> Token:
		is_decimal = False
		number = ""

		while self._current_chr is not None:
			if not Char.match(self._current_chr, Char.DOT) and not Char.match(self._current_chr, Char.DIGIT):
				break

			number += self._current_chr

			if Char.match(self._current_chr, Char.DOT):
				if is_decimal:
					raise InvalidNumber(number)
				is_decimal = True

			self._next()

		if number.endswith('.'):
			raise InvalidNumber(number)
		if number.startswith('.'):
			number = '0' + number

		return Token(Token.Type.NUMBER, number)

	# - Getters & Setters ------------------------------------------------------
	@property
	def _current_chr(self) -> str|None:
		return self._source_pkt.pick()

	def _next(self) -> None:
		self._source_pkt.consume()
