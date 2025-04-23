from __future__ import annotations
from typing import Iterable, List

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

		# ... = ?
		if self._isTokenType({ Token.Type.QUESTION }):
			self._next()
			return EvalNode(left)

		right = self._expectExpression()

		# ... = ... ?
		if self._isTokenType({ Token.Type.QUESTION }):
			self._next()
			return EquationNode(left, right)

		# x = ...
		if isinstance(left, VariableCallNode):
			return VariableDefNode(left.name, right)
		# f(x) = ...
		if isinstance(left, FunctionCallNode) and isinstance(left.parameter, VariableCallNode):
			return FunctionDefNode(left.name, left.parameter.name, right)

		# ... = ...
		raise InvalidSyntax(self._current_tkn, Token.Type.QUESTION)

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
		# ... ** ...
		# ... / ...
		# ... % ...
		while True:
			if not self._isTokenType({ Token.Type.MUL, Token.Type.MUL_MAT, Token.Type.DIV, Token.Type.MOD }):
				return left

			op = \
				BinaryOpNode.Type.MUL     if self._isTokenType({ Token.Type.MUL })     else \
				BinaryOpNode.Type.MUL_MAT if self._isTokenType({ Token.Type.MUL_MAT }) else \
				BinaryOpNode.Type.DIV     if self._isTokenType({ Token.Type.DIV })     else \
				BinaryOpNode.Type.MOD

			self._next()

			left = BinaryOpNode(op, left, self._expectPow())

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

		# VarCall / FunCall
		if self._isTokenType({ Token.Type.IDENTIFIER }):
			var = self._expectVarCall()

			if self._isTokenType({ Token.Type.PAREN_L }):
				fun = self._expectFunCall()
				fun.name = var.name
				return fun

			return var

		if self._isTokenType({ Token.Type.BRACK_L }):
			return self._expectMatrix()

		# ( Expr )
		if self._isTokenType({ Token.Type.PAREN_L }):
			self._next()

			expr = self._expectExpression()

			if not self._isTokenType({ Token.Type.PAREN_R }):
				raise InvalidSyntax(self._current_tkn, { Token.Type.PAREN_R })

			self._next()

			if self._isTokenType({ Token.Type.IDENTIFIER }):
				return BinaryOpNode(BinaryOpNode.Type.MUL, expr, self._expectPow())

			return expr

		raise InvalidSyntax(self._current_tkn, { Token.Type.NUMBER, Token.Type.IDENTIFIER, Token.Type.BRACK_L, Token.Type.PAREN_L })

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

	def _expectMatrix(self) -> MatrixNode:
		if not self._isTokenType({ Token.Type.BRACK_L }):
			raise InvalidSyntax(self._current_tkn, { Token.Type.BRACK_L })

		self._next()

		rows, cols = -1, -1
		mat : List[List[NumberNode]] = []

		# Rows
		while True:
			if not self._isTokenType({ Token.Type.BRACK_L }):
				raise InvalidSyntax(self._current_tkn, { Token.Type.BRACK_L })

			self._next()

			# Columns
			row : List[ NumberNode ] = []
			while True:
				# Row too long
				if cols != -1 and len(row) > cols:
					raise InvalidSyntax(self._current_tkn, { Token.Type.BRACK_R })

				row.append( self._expectNumber() )

				if not self._isTokenType({ Token.Type.COMMA }):
					# Row too short
					if cols != -1 and len(row) != cols:
						raise InvalidSyntax(self._current_tkn, { Token.Type.COMMA })
					break

				self._next()

			if not self._isTokenType({ Token.Type.BRACK_R }):
				raise InvalidSyntax(self._current_tkn, { Token.Type.BRACK_R })

			self._next()

			if cols == -1:
				cols = len(row)

			mat.append(row)
			rows = len(mat)

			if not self._isTokenType({ Token.Type.SEMICOLON }):
				break

			self._next()

		if not self._isTokenType({ Token.Type.BRACK_R }):
			raise InvalidSyntax(self._current_tkn, { Token.Type.BRACK_R })

		self._next()

		matrix = Matrix(rows, cols)

		for i in range(rows):
			for j in range(cols):
				matrix.set(i+1, j+1, mat[i][j].value)

		return MatrixNode(matrix)

	def _expectVarCall(self) -> VariableCallNode:
		if not self._isTokenType({ Token.Type.IDENTIFIER }):
			raise InvalidSyntax(self._current_tkn, { Token.Type.IDENTIFIER })

		assert(self._current_tkn is not None)
		assert(self._current_tkn.value is not None)

		name = self._current_tkn.value

		self._next()

		return VariableCallNode(name)

	def _expectFunCall(self) -> FunctionCallNode:
		if not self._isTokenType({ Token.Type.PAREN_L }):
			raise InvalidSyntax(self._current_tkn, { Token.Type.PAREN_L })

		self._next()

		fun_param = self._expectExpression()

		if not self._isTokenType({ Token.Type.PAREN_R }):
			raise InvalidSyntax(self._current_tkn, { Token.Type.PAREN_R })

		self._next()

		return FunctionCallNode('', fun_param)

	# - Checkers & Converters --------------------------------------------------
	def _isTokenType(self, allowed_types: set[Token.Type]):
		return self._current_tkn is not None and self._current_tkn.type in allowed_types

	# - Getters & Setters ------------------------------------------------------
	@property
	def _current_tkn(self) -> Token|None:
		return self._tokens_pkt.pick()

	def _next(self) -> None:
		self._tokens_pkt.consume()
