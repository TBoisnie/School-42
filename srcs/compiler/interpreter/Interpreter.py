from __future__ import annotations
from typing import cast

from compiler.context.Context import Context
from compiler.context.BuiltIn import BuiltIn
from compiler.interpreter.Error import *
from compiler.parser.Node import *
from compiler.types.Fraction import Fraction

class Interpreter(VisitorInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self) -> None:
		pass

	# - Methods ----------------------------------------------------------------
	def run(self, ast: Node, ctx: Context) -> StatementNode:
		self._ast = ast
		self._context = ctx

		return cast(StatementNode, ast.accept(self))

	# - Interfaces -------------------------------------------------------------
	def visitVariableDef(self, var_def: VariableDefNode) -> VariableDefNode:
		var_def.value = cast(ExpressionNode, var_def.value.accept(self))

		return var_def

	def visitFunctionDef(self, fun_def: FunctionDefNode) -> FunctionDefNode:
		ctx = self._context.clone()

		self._context.setVariable(fun_def.arg, VariableCallNode(fun_def.arg))

		fun_def.body = cast(ExpressionNode, fun_def.body.accept(self))

		self._context = ctx

		return fun_def

	def visitEval(self, eval: EvalNode) -> ExpressionNode:
		eval.body = cast(ExpressionNode, eval.body.accept(self))

		return eval.body

	def visitEquation(self, eq: EquationNode) -> EquationNode:
		ctx = self._context.clone()

		unknown = self._findEquationUnknown(eq.left)
		if unknown is not None:
			self._context.setVariable(unknown, VariableCallNode(unknown))

		eq.left = cast(ExpressionNode, eq.left.accept(self))

		self._context = ctx

		return eq

	def visitBinaryOp(self, op: BinaryOpNode) -> ExpressionNode:
		op.left = cast(ExpressionNode, op.left.accept(self))
		op.right = cast(ExpressionNode, op.right.accept(self))

		if not isinstance(op.left, ValueNode) or not isinstance(op.right, ValueNode):
			return op

		match op.op:
			case BinaryOpNode.Type.ADD:
				return self._add(op)
			case BinaryOpNode.Type.SUB:
				return self._sub(op)
			case BinaryOpNode.Type.MUL:
				return self._mul(op)
			case BinaryOpNode.Type.MUL_MAT:
				return self._mulMat(op)
			case BinaryOpNode.Type.DIV:
				return self._div(op)
			case BinaryOpNode.Type.MOD:
				return self._mod(op)
			case BinaryOpNode.Type.POW:
				return self._pow(op)

	def visitUnaryOp(self, op: UnaryOpNode) -> ExpressionNode:
		op.value = cast(ExpressionNode, op.value.accept(self))

		if not isinstance(op.value, ValueNode):
			return op

		match op.op:
			case UnaryOpNode.Type.NEG:
				return self._neg(op)

	def visitVariableCall(self, var_call: VariableCallNode) -> ExpressionNode:
		return var_call

	def visitFunctionCall(self, fun_call: FunctionCallNode) -> ExpressionNode:
		fun_call.parameter = cast(ExpressionNode, fun_call.parameter.accept(self))

		if self._context.isReservedFunctionName(fun_call.name):
			if isinstance(fun_call.parameter, ValueNode):
				return self._builtInCall(fun_call)
			return fun_call

		fun_def = self._context.getFunction(fun_call.name)

		ctx = self._context.clone()

		self._context.setVariable(fun_def['arg'], fun_call.parameter)

		fun_value = fun_def['value'].clone().accept(self)

		self._context = ctx

		return fun_value

	def visitNumber(self, number: NumberNode) -> NumberNode:
		return number

	def visitMatrix(self, matrix: MatrixNode) -> MatrixNode:
		return matrix

	def visitComplex(self, complex: ComplexNode) -> ComplexNode:
		return complex

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_ast: Node
	_context: Context

	# - Methods ----------------------------------------------------------------
	def _add(self, add: BinaryOpNode) -> ExpressionNode:
		# Matrix / Matrix
		if isinstance(add.left, MatrixNode) and isinstance(add.right, MatrixNode):
			return MatrixNode(add.left.value + add.right.value)
		# Complex / ...
		if isinstance(add.left, ComplexNode):
			# Complex / Complex
			if isinstance(add.right, ComplexNode):
				res = add.left.value + add.right.value
				return NumberNode(Number(res.re)) if res.isReal() else ComplexNode(res)
			# Complex / Number
			if isinstance(add.right, NumberNode):
				return ComplexNode(add.left.value + Complex(add.right.value.value, Fraction.null()))
		# Number / ...
		if isinstance(add.left, NumberNode):
			# Number / Complex
			if isinstance(add.right, ComplexNode):
				return ComplexNode(Complex(add.left.value.value, Fraction.null()) + add.right.value)
			# Number / Number
			if isinstance(add.right, NumberNode):
				return NumberNode(add.left.value + add.right.value)

		raise UnsupportedOperator(add.op, f"Can't add {add.left.__class__.__name__} to {add.right.__class__.__name__}")

	def _sub(self, sub: BinaryOpNode) -> ExpressionNode:
		# Matrix / Matrix
		if isinstance(sub.left, MatrixNode) and isinstance(sub.right, MatrixNode):
			return MatrixNode(sub.left.value - sub.right.value)
		# Complex / ...
		if isinstance(sub.left, ComplexNode):
			# Complex / Complex
			if isinstance(sub.right, ComplexNode):
				res = sub.left.value - sub.right.value
				return NumberNode(Number(res.re)) if res.isReal() else ComplexNode(res)
			# Complex / Number
			if isinstance(sub.right, NumberNode):
				return ComplexNode(sub.left.value - Complex(sub.right.value.value, Fraction.null()))
		# Number
		if isinstance(sub.left, NumberNode):
			# Number / Complex
			if isinstance(sub.right, ComplexNode):
				return ComplexNode(Complex(sub.left.value.value, Fraction.null()) - sub.right.value)
			# Number / Number
			if isinstance(sub.right, NumberNode):
				return NumberNode(sub.left.value - sub.right.value)

		raise UnsupportedOperator(sub.op, f"Can't substract {sub.left.__class__.__name__} by {sub.left.__class__.__name__}.")

	def _mul(self, mul: BinaryOpNode) -> ExpressionNode:
		# Matrix / ...
		if isinstance(mul.left, MatrixNode):
			# Matrix / Matrix
			if isinstance(mul.right, MatrixNode):
				return MatrixNode(mul.left.value * mul.right.value)
			# Matrix / Number
			if isinstance(mul.right, NumberNode):
				return MatrixNode(mul.left.value * Matrix(mul.left.value.rows, mul.left.value.cols, mul.right.value))
		# Complex / ...
		if isinstance(mul.left, ComplexNode):
			# Complex / Complex
			if isinstance(mul.right, ComplexNode):
				res = mul.left.value * mul.right.value
				return NumberNode(Number(res.re)) if res.isReal() else ComplexNode(res)
			# Complex / Number
			if isinstance(mul.right, NumberNode):
				res = mul.left.value * Complex(mul.right.value.value, Fraction.null())
				return NumberNode(Number(res.re)) if res.isReal() else ComplexNode(res)
		# Number / ...
		if isinstance(mul.left, NumberNode):
			# Number / Matrix
			if isinstance(mul.right, MatrixNode):
				return MatrixNode(mul.right.value * Matrix(mul.right.value.rows, mul.right.value.cols, mul.left.value))
			# Number / Complex
			if isinstance(mul.right, ComplexNode):
				res = Complex(mul.left.value.value, Fraction.null()) * mul.right.value
				return NumberNode(Number(res.re)) if res.isReal() else ComplexNode(res)
			# Number / Number
			if isinstance(mul.right, NumberNode):
				return NumberNode(mul.left.value * mul.right.value)

		raise UnsupportedOperator(mul.op, f"Can't multiply {mul.left.__class__.__name__} by {mul.right.__class__.__name__}.")

	def _mulMat(self, mulmat: BinaryOpNode) -> ExpressionNode:
		if not isinstance(mulmat.left, MatrixNode) or not isinstance(mulmat.right, MatrixNode) :
			raise UnsupportedOperator(mulmat.op, f"MulMat requires 2 matrices.")

		# Matrix
		return MatrixNode(mulmat.left.value @ mulmat.right.value)

	def _div(self, div: BinaryOpNode) -> ExpressionNode:
		if isinstance(div.left, MatrixNode):
			raise UnsupportedOperator(div.op, f"Can't divide a matrix.")

		# Complex / ...
		if isinstance(div.left, ComplexNode):
			# Complex / Complex
			if isinstance(div.right, ComplexNode):
				return ComplexNode(div.left.value / div.right.value)
			# Complex / Number
			if isinstance(div.right, NumberNode):
				return ComplexNode(div.left.value / Complex(div.right.value.value, Fraction.null()))
		# Number / ...
		if isinstance(div.left, NumberNode):
			# Number / Complex
			if isinstance(div.right, ComplexNode):
				return ComplexNode(Complex(div.left.value.value, Fraction.null()) / div.right.value)
			# Number / Number
			if isinstance(div.right, NumberNode):
				return NumberNode(div.left.value / div.right.value)

		raise UnsupportedOperator(div.op, f"Can't divide {div.left.__class__.__name__} by {div.right.__class__.__name__}.")

	def _mod(self, mod: BinaryOpNode) -> ExpressionNode:
		if not isinstance(mod.left, NumberNode) or not isinstance(mod.right, NumberNode):
			raise UnsupportedOperator(mod.op, f"Modulo requires 2 integers.")
		if not mod.left.value.isInt() or not mod.right.value.isInt():
			raise UnsupportedOperator(mod.op, f"Modulo requires 2 integers.")

		# Number
		return NumberNode(mod.left.value % mod.right.value)

	def _pow(self, pow: BinaryOpNode) -> ExpressionNode:
		if not isinstance(pow.right, NumberNode) or not pow.right.value.isInt() or pow.right.value.toInt() < 0:
			raise UnsupportedOperator(pow.op, f"Exponent must be a positive integer.")

		# Matrix
		if isinstance(pow.left, MatrixNode):
			return MatrixNode(pow.left.value ** pow.right.value)
		# Complex
		if isinstance(pow.left, ComplexNode):
			return ComplexNode(pow.left.value ** pow.right.value)
		# Number
		if isinstance(pow.left, NumberNode):
			return NumberNode(pow.left.value ** pow.right.value)

		raise UnsupportedOperator(pow.op, f"Can't pow with {pow.left.__class__.__name__} base.")

	def _neg(self, neg: UnaryOpNode) -> ExpressionNode:
		# Matrix
		if isinstance(neg.value, NumberNode):
			return NumberNode(-neg.value.value)
		# Complex
		if isinstance(neg.value, MatrixNode):
			return MatrixNode(-neg.value.value)
		# Number
		if isinstance(neg.value, ComplexNode):
			return ComplexNode(-neg.value.value)

		raise UnsupportedOperator(neg.op, f"Can't negate {neg.value.__class__.__name__}.")

	def _findEquationUnknown(self, expr: ExpressionNode) -> str|None:
		if isinstance(expr, VariableCallNode):
			return expr.name

		if isinstance(expr, BinaryOpNode):
			unknown = self._findEquationUnknown(expr.left)

			if unknown is None:
				return self._findEquationUnknown(expr.right)

			return unknown

		if isinstance(expr, UnaryOpNode):
			return self._findEquationUnknown(expr.value)

		return None

	def _builtInCall(self, fun_call: FunctionCallNode) -> ExpressionNode:
		match fun_call.name.lower():
			case 'abs':
				if not isinstance(fun_call.parameter, NumberNode) \
				and not isinstance(fun_call.parameter, ComplexNode):

					raise InvalidFunctionParameter(fun_call.name, f"Parameter must be a number or a complex.")

				return NumberNode(BuiltIn.abs(fun_call.parameter.value))

			case 'sqrt':
				if not isinstance(fun_call.parameter, NumberNode) \
					or fun_call.parameter.value.toFloat() < 0.0:

					raise InvalidFunctionParameter(fun_call.name, f"Parameter must be a positive number.")

				return NumberNode(BuiltIn.sqrt(fun_call.parameter.value))

			case 'floor':
				if not isinstance(fun_call.parameter, NumberNode):
					raise InvalidFunctionParameter(fun_call.name, f"Parameter must be a number.")

				return NumberNode(BuiltIn.floor(fun_call.parameter.value))

			case 'ceil':
				if not isinstance(fun_call.parameter, NumberNode):
					raise InvalidFunctionParameter(fun_call.name, f"Parameter must be a number.")

				return NumberNode(BuiltIn.ceil(fun_call.parameter.value))

			case 'rad':
				if not isinstance(fun_call.parameter, NumberNode):
					raise InvalidFunctionParameter(fun_call.name, f"Parameter must be a number.")

				return NumberNode(BuiltIn.rad(fun_call.parameter.value))

			case 'trace':
				if not isinstance(fun_call.parameter, MatrixNode) \
					or not fun_call.parameter.value.isSquare():

					raise InvalidFunctionParameter(fun_call.name, f"Parameter must be a square matrix.")

				return NumberNode(BuiltIn.trace(fun_call.parameter.value))

			case 'transpose':
				if not isinstance(fun_call.parameter, MatrixNode):
					raise InvalidFunctionParameter(fun_call.name, f"Parameter must be a matrix.")

				return MatrixNode(BuiltIn.transpose(fun_call.parameter.value))

			case _:
				raise NotImplementedBuiltIn(fun_call.name)
