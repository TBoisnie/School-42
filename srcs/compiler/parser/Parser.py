from __future__ import annotations
from typing import Iterable

from compiler.lexer.Token import Token
from compiler.parser.Error import InvalidSyntax
from compiler.parser.Node import *
from utilities.Pickator import Pickator
from utilities.Char import Char

class Parser:
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self):
		self._tokens_pkt = Pickator([])

	# - Methods ----------------------------------------------------------------
	def build(self, tkns_itr: Iterable[Token]) -> Node:
		self._tokens_pkt = Pickator(tkns_itr)

		stmt = self._expectStatement()

		allowed_types = { Token.Type.END }
		if not self._isTokenType(allowed_types):
			raise InvalidSyntax(self._current_tkn, allowed_types)

		return stmt

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_tokens_pkt: Pickator[Token]

	# - Methods ----------------------------------------------------------------
	# ---- Statements ----------------------------------------------------------
	def _expectStatement(self) -> StatementNode:
		left = self._expectExpression()

		# ... =
		allowed_types = { Token.Type.EQUAL }
		if not self._isTokenType(allowed_types):
			raise InvalidSyntax(self._current_tkn, allowed_types)

		self._next()

		right = self._expectExpression()

		# ... = ... ...
		if not self._isTokenType({ Token.Type.END }):
			raise InvalidSyntax(self._current_tkn, Token.Type.END)

		# ... = ...
		return EquationNode(left, right)

	# ---- Expressions ---------------------------------------------------------
	def _expectExpression(self) -> ExpressionNode:
		return self._expectAddOrSub()

	def _expectAddOrSub(self) -> ExpressionNode:
		left = self._expectMulOrDiv()

		# ... + ...
		# ... - ...
		while True:
			if not self._isTokenType({ Token.Type.ADD, Token.Type.SUB }):
				return left

			op = \
				BinaryOpNode.Type.ADD if self._isTokenType({ Token.Type.ADD }) else \
				BinaryOpNode.Type.SUB

			self._next()

			left = BinaryOpNode(op, left, self._expectMulOrDiv())

	def _expectMulOrDiv(self) -> ExpressionNode:
		left = self._expectPow()

		# ... * ...
		while True:
			if not self._isTokenType({ Token.Type.MUL, }):
				return left

			self._next()

			left = BinaryOpNode(BinaryOpNode.Type.MUL, left, self._expectPow())

	def _expectPow(self) -> ExpressionNode:
		left = self._expectNeg()

		# ... ^ ...
		while True:
			if not self._isTokenType({ Token.Type.POW }):
				return left

			op = BinaryOpNode.Type.POW

			self._next()

			left = BinaryOpNode(op, left, self._expectNeg())

	def _expectNeg(self) -> ExpressionNode:
		# - ...
		if not self._isTokenType({ Token.Type.SUB }):
			return self._expectTerm()

		op = UnaryOpNode.Type.NEG

		self._next()

		return UnaryOpNode(op, self._expectPow())

	# ---- Term ----------------------------------------------------------------
	def _expectTerm(self) -> ExpressionNode:
		# Number / Number VarCall
		if self._isTokenType({ Token.Type.NUMBER }):
			number = self._expectNumber()

			if self._isTokenType({ Token.Type.IDENTIFIER }):
				return BinaryOpNode(BinaryOpNode.Type.MUL, number, self._expectPow())

			return number

		# VarCall
		if self._isTokenType({ Token.Type.IDENTIFIER }):
			var = self._expectVarCall()
			return var

		raise InvalidSyntax(self._current_tkn, { Token.Type.NUMBER, Token.Type.IDENTIFIER })

	def _expectNumber(self) -> NumberNode:
		if not self._isTokenType({ Token.Type.NUMBER }):
			raise InvalidSyntax(self._current_tkn, { Token.Type.NUMBER })

		assert(self._current_tkn is not None)
		assert(self._current_tkn.value is not None)

		if Char.DOT in self._current_tkn.value:
			num = float(self._current_tkn.value)
		else:
			num = int(self._current_tkn.value)

		self._next()

		return NumberNode(Number.fromLiteral(num))

	def _expectVarCall(self) -> VariableCallNode:
		if not self._isTokenType({ Token.Type.IDENTIFIER }):
			raise InvalidSyntax(self._current_tkn, { Token.Type.IDENTIFIER })

		assert(self._current_tkn is not None)
		assert(self._current_tkn.value is not None)

		name = self._current_tkn.value

		self._next()

		return VariableCallNode(name)

	# - Checkers & Converters --------------------------------------------------
	def _isTokenType(self, allowed_types: set[Token.Type]):
		return self._current_tkn is not None and self._current_tkn.type in allowed_types

	# - Getters & Setters ------------------------------------------------------
	@property
	def _current_tkn(self) -> Token|None:
		return self._tokens_pkt.pick()

	def _next(self) -> None:
		self._tokens_pkt.consume()
