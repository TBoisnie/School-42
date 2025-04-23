from __future__ import annotations
from typing import cast, TypedDict

from compiler.context.Context import Context
from compiler.context.Error import UnknownVariable
from compiler.parser.Node import *

VariableParamsType = TypedDict('VariableParams', { 'factor': ExpressionNode, 'variable': VariableCallNode, 'exponent': ExpressionNode })

class Optimizer(VisitorInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self) -> None:
		pass

	# - Methods ----------------------------------------------------------------
	def optimize(self, ast: Node, ctx: Context, factorize: bool) -> StatementNode:
		self._ast = ast
		self._context = ctx
		self._factorize = factorize

		return cast(StatementNode, self._ast.accept(self))

	# - Interfaces -------------------------------------------------------------
	def visitVariableDef(self, var_def: VariableDefNode) -> VariableDefNode:
		value = self._replaceVariables(var_def.value)
		var_def.value = cast(ExpressionNode, value.accept(self))

		return var_def

	def visitFunctionDef(self, fun_def: FunctionDefNode) -> FunctionDefNode:
		ctx = self._context.clone()

		self._context.setVariable(fun_def.arg, VariableCallNode(fun_def.arg))

		body = self._replaceVariables(fun_def.body)
		fun_def.body = cast(ExpressionNode, body.accept(self))

		self._context = ctx

		return fun_def

	def visitEval(self, eval: EvalNode) -> EvalNode:
		body = self._replaceVariables(eval.body)
		eval.body = cast(ExpressionNode, body.accept(self))

		return eval

	def visitEquation(self, eq: EquationNode) -> EquationNode:
		eq.left = BinaryOpNode(BinaryOpNode.Type.SUB, eq.left, eq.right)
		eq.right = NumberNode(Number.fromLiteral(0))

		left = self._replaceVariables(eq.left)
		eq.left = cast(ExpressionNode, left.accept(self))

		return eq

	def visitBinaryOp(self, op: BinaryOpNode) -> ExpressionNode:
		op.left = cast(ExpressionNode, op.left.accept(self))
		op.right = cast(ExpressionNode, op.right.accept(self))

		if self._isValueNodeTree(op.left) and self._isValueNodeTree(op.right):
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

		match op.op:
			case UnaryOpNode.Type.NEG:
				return self._neg(op)

	def visitVariableCall(self, var_call: VariableCallNode) -> ExpressionNode:
		return var_call

	def visitFunctionCall(self, fun_call: FunctionCallNode) -> ExpressionNode:
		fun_call.parameter = cast(ExpressionNode, fun_call.parameter.accept(self))

		if self._context.isReservedFunctionName(fun_call.name):
			return fun_call

		fun_def = self._context.getFunction(fun_call.name)

		ctx = self._context.clone()

		self._context.setVariable(fun_def['arg'], fun_call.parameter)

		fun_value = self._replaceVariables(fun_def['value'].clone()).accept(self)

		self._context = ctx

		return cast(ExpressionNode, fun_value)

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
	_factorize: bool

	# - Methods ----------------------------------------------------------------
	def _add(self, add: BinaryOpNode) -> ExpressionNode:

		if not self._isValueNodeTree(add.left) \
			and self._isValueNodeTree(add.right):
			# NotValue + Value == Value + NotValue
			add.left, add.right = add.right, add.left

		var_left = self._getVariableParams(add.left)
		var_right = self._getVariableParams(add.right)

		if var_left is not None:
			if var_right is not None:
				if var_left['variable'] == var_right['variable']:
					if var_left['exponent'] == var_right['exponent']:
						# VarA + VarA == (1 + 1) * VarA
						# (Any * VarA) + VarA == (Any + 1) * VarA
						# VarA + (Any * VarA) == (Any + 1) * VarA
						# (AnyA * VarA) + (AnyB * VarA) == (AnyA + AnyB) * VarA
						left = BinaryOpNode(BinaryOpNode.Type.ADD, var_left['factor'], var_right['factor'])
						right = BinaryOpNode(BinaryOpNode.Type.POW, var_left['variable'], var_left['exponent'])
						op = BinaryOpNode(BinaryOpNode.Type.MUL, left, right)
						return cast(ExpressionNode, op.accept(self))

					if not self._isNumberAndLowerThan(var_left['exponent'], var_right['exponent']):
						# VarA ^ 2 + VarA ^ 1 = VarA ^ 1 + VarA ^ 2
						add.left, add.right = add.right, add.left
						return cast(ExpressionNode, add.accept(self))

				elif var_left['variable'].name > var_right['variable'].name:
					# VarB + VarA == VarA + VarB
					add.left, add.right = add.right, add.left
					return cast(ExpressionNode, add.accept(self))
			else:
				# Var + NotVar == NotVar + Var
				add.left, add.right = add.right, add.left
				return cast(ExpressionNode, add.accept(self))

		if isinstance(add.left, UnaryOpNode):
			match add.left.op:
				case UnaryOpNode.Type.NEG:
					if not self._isValueNodeTree(add.left.value) \
						and var_right is None:
						# (- NotValue) + Any == Any - NotValue
						add.left, add.right = add.right, add.left.value
						add.op = BinaryOpNode.Type.SUB
						return cast(ExpressionNode, add.accept(self))
				case _:
					pass

		if isinstance(add.left, BinaryOpNode):
			match add.left.op:
				case BinaryOpNode.Type.ADD:
					if not self._isValueNodeTree(add.left.right) \
						and self._isValueNodeTree(add.right):
						# (Any + NotValue) + Value == (Any + Value) + NotValue
						add.left.right, add.right = add.right, add.left.right
						return cast(ExpressionNode, add.accept(self))

					if var_right is not None:
						var_left_right = self._getVariableParams(add.left.right)

						if var_left_right is not None:
							if var_left_right['variable'] == var_right['variable']:
								if var_left_right['exponent'] == var_right['exponent']:
									# (Any + VarA) + VarA == (VarA + VarA) + Any
									add.left.left, add.right = add.right, add.left.left
									return cast(ExpressionNode, add.accept(self))

								if not self._isNumberAndLowerThan(var_left_right['exponent'], var_right['exponent']):
									# (Any + VarA ^ 2) + VarA ^ 1 = (Any + VarA ^ 1) + VarA ^ 2
									add.left.right, add.right = add.right, add.left.right
									return cast(ExpressionNode, add.accept(self))

							elif var_left_right['variable'].name > var_right['variable'].name:
								# (Any + VarB) + VarA == (Any + VarA) + VarB
								add.left.right, add.right = add.right, add.left.right
								return cast(ExpressionNode, add.accept(self))

						elif not self._isValueNodeTree(add.left.right):
							# (Any + NotValueOrVar) + Var == (Any + Var) + NotValueOrVar
							add.left.right, add.right = add.right, add.left.right
							return cast(ExpressionNode, add.accept(self))

				case BinaryOpNode.Type.SUB:
					if not self._isValueNodeTree(add.left.right) \
						and self._isValueNodeTree(add.right):
						# (Any - NotValue) + Value == (Any + Value) - NotValue
						add.left.right, add.right = add.right, add.left.right
						add.left.op = BinaryOpNode.Type.ADD
						add.op = BinaryOpNode.Type.SUB
						return cast(ExpressionNode, add.accept(self))

					if var_right is not None:
						var_left_right = self._getVariableParams(add.left.right)

						if var_left_right is not None:
							if var_left_right['variable'] == var_right['variable']:
								if var_left_right['exponent'] == var_right['exponent']:
									# (Any - VarA1) + VarA2 == (VarA2 - VarA1) + Any
									add.left.left, add.right = add.right, add.left.left
									return cast(ExpressionNode, add.accept(self))

								if not self._isNumberAndLowerThan(var_left_right['exponent'], var_right['exponent']):
									# (Any - VarA ^ 2) + VarA ^ 1 = (Any + VarA ^ 1) - VarA ^ 2
									add.left.right, add.right = add.right, add.left.right
									add.left.op = BinaryOpNode.Type.ADD
									add.op = BinaryOpNode.Type.SUB
									return cast(ExpressionNode, add.accept(self))

							elif var_left_right['variable'].name > var_right['variable'].name:
								# (Any - VarB) + VarA == (Any + VarA) - VarB
								add.left.right, add.right = add.right, add.left.right
								add.left.op = BinaryOpNode.Type.ADD
								add.op = BinaryOpNode.Type.SUB
								return cast(ExpressionNode, add.accept(self))

						elif not self._isValueNodeTree(add.left.right):
							# (Any - NotValueOrVar) + Var == (Any + Var) - NotValueOrVar
							add.left.right, add.right = add.right, add.left.right
							add.left.op = BinaryOpNode.Type.ADD
							add.op = BinaryOpNode.Type.SUB
							return cast(ExpressionNode, add.accept(self))
				case _:
					pass

		if isinstance(add.right, UnaryOpNode):
			match add.right.op:
				case UnaryOpNode.Type.NEG:
					# AnyA + (- AnyB) == AnyA - AnyB
					add.right = add.right.value
					add.op = BinaryOpNode.Type.SUB
					return cast(ExpressionNode, add.accept(self))
				case _:
					pass

		if isinstance(add.right, BinaryOpNode):
			match add.right.op:
				case BinaryOpNode.Type.ADD:
					# AnyA + (AnyB + AnyC) == (AnyA + AnyB) + AnyC
					add.left, add.right = add.right, add.left
					add.left.left, add.left.right = add.left.right, add.left.left
					add.left.left, add.right = add.right, add.left.left
					return cast(ExpressionNode, add.accept(self))
				case BinaryOpNode.Type.SUB:
					# AnyA + (AnyB - AnyC) == (AnyA + AnyB) - AnyC
					add.left, add.right = add.right, add.left
					add.left.op = BinaryOpNode.Type.ADD
					add.left.left, add.left.right = add.left.right, add.left.left
					add.left.left, add.right = add.right, add.left.left
					add.op = BinaryOpNode.Type.SUB
					return cast(ExpressionNode, add.accept(self))
				case _:
					pass

		return add

	def _sub(self, sub: BinaryOpNode) -> ExpressionNode:

		if not self._isValueNodeTree(sub.left) \
			and self._isValueNodeTree(sub.right):
			# NotValue - Value == (- Value) + NotValue
			sub.left, sub.right = UnaryOpNode(UnaryOpNode.Type.NEG, sub.right), sub.left
			sub.op = BinaryOpNode.Type.ADD
			return cast(ExpressionNode, sub.accept(self))

		var_left = self._getVariableParams(sub.left)
		var_right = self._getVariableParams(sub.right)

		if var_left is not None:
			if var_right is not None:
				if var_left['variable'] == var_right['variable']:
					if var_left['exponent'] == var_right['exponent']:
						# VarA - VarA == (1 - 1) * VarA
						# (Any * VarA) - VarA == (Any - 1) * VarA
						# VarA + (Any * VarA) == (Any - 1) * VarA
						# (AnyA * VarA) - (AnyB * VarA) == (AnyA - AnyB) * VarA
						left = BinaryOpNode(BinaryOpNode.Type.SUB, var_left['factor'], var_right['factor'])
						right = BinaryOpNode(BinaryOpNode.Type.POW, var_left['variable'], var_left['exponent'])
						op = BinaryOpNode(BinaryOpNode.Type.MUL, left, right)
						return cast(ExpressionNode, op.accept(self))

					if not self._isNumberAndLowerThan(var_left['exponent'], var_right['exponent']):
						# VarA ^ 2 - VarA ^ 1 = (- VarA ^ 1) + VarA ^ 2
						sub.left, sub.right = UnaryOpNode(UnaryOpNode.Type.NEG, sub.right), sub.left
						sub.op = BinaryOpNode.Type.ADD
						return cast(ExpressionNode, sub.accept(self))

				elif var_left['variable'].name > var_right['variable'].name:
					# VarB - VarA == (- VarA) + VarB
					left = UnaryOpNode(UnaryOpNode.Type.NEG, sub.right)
					right = sub.left
					op = BinaryOpNode(BinaryOpNode.Type.ADD, left, right)
					return cast(ExpressionNode, op.accept(self))
			else:
				# Var - NotVar == -NotVar + Var
				sub.left, sub.right = UnaryOpNode(UnaryOpNode.Type.NEG, sub.right), sub.left
				sub.op = BinaryOpNode.Type.ADD
				return cast(ExpressionNode, sub.accept(self))

		if isinstance(sub.left, BinaryOpNode):
			match sub.left.op:
				case BinaryOpNode.Type.ADD:
					if not self._isValueNodeTree(sub.left.right) \
						and self._isValueNodeTree(sub.right):
						# (Any + NotValue) - Value == (Any - Value) + NotValue
						sub.left.right, sub.right = sub.right, sub.left.right
						sub.left.op = BinaryOpNode.Type.SUB
						sub.op = BinaryOpNode.Type.ADD
						return cast(ExpressionNode, sub.accept(self))

					if var_right is not None:
						var_left_right = self._getVariableParams(sub.left.right)

						if var_left_right is not None:
							if var_left_right['variable'] == var_right['variable']:
								if var_left_right['exponent'] == var_right['exponent']:
									# (Any + VarA1) - VarA2 == (VarA1 - VarA2) + Any
									sub.left.left, sub.right = sub.right, sub.left.left
									sub.op = BinaryOpNode.Type.ADD
									sub.left.left, sub.left.right = sub.left.right, sub.left.left
									sub.left.op = BinaryOpNode.Type.SUB
									return cast(ExpressionNode, sub.accept(self))

								if not self._isNumberAndLowerThan(var_left_right['exponent'], var_right['exponent']):
									# (Any + VarA ^ 2) - VarA ^ 1 = (Any - VarA ^ 1) + VarA ^ 2
									sub.left.right, sub.right = sub.right, sub.left.right
									sub.left.op = BinaryOpNode.Type.SUB
									sub.op = BinaryOpNode.Type.ADD
									return cast(ExpressionNode, sub.accept(self))

							elif var_left_right['variable'].name > var_right['variable'].name:
								# (Any + VarB) - VarA == (Any - VarA) + VarB
								sub.left.right, sub.right = sub.right, sub.left.right
								sub.left.op = BinaryOpNode.Type.SUB
								sub.op = BinaryOpNode.Type.ADD
								return cast(ExpressionNode, sub.accept(self))

						elif not self._isValueNodeTree(sub.left.right):
							# (Any + NotValueOrVar) - Var == (Any - Var) + NotValueOrVar
							sub.left.right, sub.right = sub.right, sub.left.right
							sub.left.op = BinaryOpNode.Type.SUB
							sub.op = BinaryOpNode.Type.ADD
							return cast(ExpressionNode, sub.accept(self))

				case BinaryOpNode.Type.SUB:
					if not self._isValueNodeTree(sub.left.right) \
						and self._isValueNodeTree(sub.right):
						# (Any - NotValue) - Value == (Any - Value) - NotValue
						sub.left.right, sub.right = sub.right, sub.left.right
						return cast(ExpressionNode, sub.accept(self))

					if var_right is not None:
						var_left_right = self._getVariableParams(sub.left.right)

						if var_left_right is not None:
							if var_left_right['variable'] == var_right['variable']:
								if var_left_right['exponent'] == var_right['exponent']:
									# (Any - VarA1) - VarA2 == (- VarA2 - VarA1) + Any
									sub.left.left, sub.right = sub.right, sub.left.left
									sub.op = BinaryOpNode.Type.ADD
									sub.left.left = UnaryOpNode(UnaryOpNode.Type.NEG, sub.left.left)
									return cast(ExpressionNode, sub.accept(self))

								if not self._isNumberAndLowerThan(var_left_right['exponent'], var_right['exponent']):
									# (Any - VarA ^ 2) - VarA ^ 1 = (Any - VarA ^ 1) - VarA ^ 2
									sub.left.right, sub.right = sub.right, sub.left.right
									return cast(ExpressionNode, sub.accept(self))

							elif var_left_right['variable'].name > var_right['variable'].name:
								# (Any - VarB) - VarA == (Any - VarA) - VarB
								sub.left.right, sub.right = sub.right, sub.left.right
								return cast(ExpressionNode, sub.accept(self))

						elif not self._isValueNodeTree(sub.left.right):
							# (Any - NotValueOrVar) - Var == (Any - Var) - NotValueOrVar
							sub.left.right, sub.right = sub.right, sub.left.right
							return cast(ExpressionNode, sub.accept(self))
				case _:
					pass

		if isinstance(sub.right, UnaryOpNode):
			match sub.right.op:
				case UnaryOpNode.Type.NEG:
					# AnyA - (- AnyB) == AnyA + AnyB
					sub.right = sub.right.value
					sub.op = BinaryOpNode.Type.ADD
					return cast(ExpressionNode, sub.accept(self))
				case _:
					pass

		if isinstance(sub.right, BinaryOpNode):
			match sub.right.op:
				case BinaryOpNode.Type.ADD:
					# AnyA - (AnyB + AnyC) == (AnyA - AnyB) - AnyC
					sub.left, sub.right = sub.right, sub.left
					sub.left.left, sub.left.right = sub.left.right, sub.left.left
					sub.left.left, sub.right = sub.right, sub.left.left
					sub.left.op = BinaryOpNode.Type.SUB
					return cast(ExpressionNode, sub.accept(self))
				case BinaryOpNode.Type.SUB:
					# AnyA - (AnyB - AnyC) == (AnyA - AnyB) + AnyC
					sub.left, sub.right = sub.right, sub.left
					sub.op = BinaryOpNode.Type.ADD
					sub.left.left, sub.left.right = sub.left.right, sub.left.left
					sub.left.left, sub.right = sub.right, sub.left.left
					return cast(ExpressionNode, sub.accept(self))
				case _:
					pass

		return sub

	def _mul(self, mul: BinaryOpNode) -> ExpressionNode:

		if not self._isValueNodeTree(mul.left) \
			and self._isValueNodeTree(mul.right):
			# NotValue * Value = Value * NotValue
			mul.left, mul.right = mul.right, mul.left

		var_left = self._getVariableParams(mul.left)
		var_right = self._getVariableParams(mul.right)

		if var_left is not None:
			if var_right is not None:
				if var_left['variable'] == var_right['variable']:
					# VarA * VarA == VarA ^ (1 + 1)
					# (Any * VarA) * VarA == Any * VarA ^ (1 + 1)
					# VarA * (Any * VarA) == Any * VarA ^ (1 + 1)
					# (AnyA * VarA) * (AnyB * VarA) == (AnyA * AnyB) * VarA ^ (1 + 1)
					exp = BinaryOpNode(BinaryOpNode.Type.ADD, var_left['exponent'], var_right['exponent'])
					left = BinaryOpNode(BinaryOpNode.Type.MUL, var_left['factor'], var_right['factor'])
					right = BinaryOpNode(BinaryOpNode.Type.POW, var_left['variable'], exp)
					op = BinaryOpNode(BinaryOpNode.Type.MUL, left, right)
					return cast(ExpressionNode, op.accept(self))

				elif var_left['variable'].name > var_right['variable'].name:
					# VarB * VarA == VarA * VarB
					mul.left, mul.right = mul.right, mul.left
					return cast(ExpressionNode, mul.accept(self))

			else:
				# Var * NotVar == NotVar * Var
				mul.left, mul.right = mul.right, mul.left
				return cast(ExpressionNode, mul.accept(self))

		if isinstance(mul.left, BinaryOpNode):
			match mul.left.op:
				case BinaryOpNode.Type.ADD|BinaryOpNode.Type.SUB:
					is_right_div = isinstance(mul.right, BinaryOpNode) \
						and mul.right.op is BinaryOpNode.Type.DIV

					if not is_right_div \
						and (
							var_right is None \
							or self._isContaningVar(mul.left, var_right['variable'].name)
						) \
						and not self._factorize:
						# (NotValue + AnyA) * NotDiv == NotValue * NotDiv + AnyA * NotDiv
						left = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left.left, mul.right)
						right = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left.right, mul.right)
						op = BinaryOpNode(mul.left.op, left, right)
						return cast(ExpressionNode, op.accept(self))

				case BinaryOpNode.Type.MUL:
					var_left_right = self._getVariableParams(mul.left.right)

					if var_left_right is not None:
						if var_right is not None:
							if var_left_right['variable'] == var_right['variable']:
								# (Any * VarA) * VarA == (VarA * VarA) * Any
								mul.left.left, mul.right = mul.right, mul.left.left
								return cast(ExpressionNode, mul.accept(self))

							elif var_left_right['variable'].name > var_right['variable'].name:
								# (Any * VarB) * VarA == (Any * VarA) * VarB
								mul.left.right, mul.right = mul.right, mul.left.right
								return cast(ExpressionNode, mul.accept(self))
						else:
							# (Any * Var) * NotVar == (Any * NotVar) * Var
							mul.left.right, mul.right = mul.right, mul.left.right
							return cast(ExpressionNode, mul.accept(self))

				case BinaryOpNode.Type.DIV:
					if not self._isValueNodeTree(mul.left.right):
						# (AnyA / NotValue) * AnyC == (AnyA * AnyC) / NotValue
						mul.left.right, mul.right = mul.right, mul.left.right
						mul.left.op = BinaryOpNode.Type.MUL
						mul.op = BinaryOpNode.Type.DIV
						return cast(ExpressionNode, mul.accept(self))
				case _:
					return mul

		if isinstance(mul.right, UnaryOpNode):
			match mul.right.op:
				case UnaryOpNode.Type.NEG:
					# Any * (- Any) == (- Any) * Any
					left = UnaryOpNode(UnaryOpNode.Type.NEG, mul.left)
					right = mul.right.value
					op = BinaryOpNode(BinaryOpNode.Type.MUL, left, right)
					return cast(ExpressionNode, op.accept(self))
				case _:
					pass

		if isinstance(mul.right, BinaryOpNode):
			match mul.right.op:
				case BinaryOpNode.Type.ADD|BinaryOpNode.Type.SUB:
					if not self._isValueNodeTree(mul.left):
						# NotValue * (AnyA + AnyB) == (AnyA + AnyB) * NotValue
						# NotValue * (AnyA - AnyB) == (AnyA - AnyB) * NotValue
						mul.left, mul.right = mul.right, mul.left
						return cast(ExpressionNode, mul.accept(self))
					if not self._factorize:
						# AnyA * (AnyB + AnyC) == (AnyA * AnyB) + (AnyA * AnyC)
						# AnyA * (AnyB - AnyC) == (AnyA * AnyB) - (AnyA * AnyC)
						left = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left, mul.right.left)
						right = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left, mul.right.right)
						op = BinaryOpNode(mul.right.op, left, right)
						return cast(ExpressionNode, op.accept(self))
				case BinaryOpNode.Type.MUL:
					# AnyA * (AnyB * AnyC) == (AnyA * AnyB) * AnyC
					mul.left = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left, mul.right.left)
					mul.right = mul.right.right
					return cast(ExpressionNode, mul.accept(self))
				case BinaryOpNode.Type.DIV:
					if not self._isValueNodeTree(mul.right.right):
						# AnyA * (AnyB / NotValue) == (AnyA * AnyB) / NotValue
						mul.left = BinaryOpNode(BinaryOpNode.Type.MUL, mul.left, mul.right.left)
						mul.op = BinaryOpNode.Type.DIV
						mul.right = mul.right.right
						return cast(ExpressionNode, mul.accept(self))
				case _:
					pass

		return mul

	def _div(self, div: BinaryOpNode) -> ExpressionNode:

		var_left = self._getVariableParams(div.left)
		var_right = self._getVariableParams(div.right)

		if var_left is not None:
			if var_right is not None:
				if var_left['variable'] == var_right['variable']:
					# (FactorA * VarA ^ ExpA) / (FactorB * VarA ^ ExpB) = (FactorA / FactorB) * VarA ^ (ExpA - ExpB)
					left = BinaryOpNode(BinaryOpNode.Type.DIV, var_left['factor'], var_right['factor'])
					exp = BinaryOpNode(BinaryOpNode.Type.SUB, var_left['exponent'], var_right['exponent'])
					right = BinaryOpNode(BinaryOpNode.Type.POW, var_left['variable'], exp)
					op = BinaryOpNode(BinaryOpNode.Type.MUL, left, right)
					return cast(ExpressionNode, op.accept(self))

		if isinstance(div.left, BinaryOpNode):
			match div.left.op:
				case BinaryOpNode.Type.ADD|BinaryOpNode.Type.SUB:
					if self._isValueNodeTree(div.right) and not self._factorize:
						# (AnyA + AnyB) / Value == (AnyA / Value) + (AnyB / Value)
						# (AnyA - AnyB) / Value == (AnyA / Value) - (AnyB / Value)
						left = BinaryOpNode(BinaryOpNode.Type.DIV, div.left.left, div.right)
						right = BinaryOpNode(BinaryOpNode.Type.DIV, div.left.right, div.right)
						op = BinaryOpNode(div.left.op, left, right)
						return cast(ExpressionNode, op.accept(self))
				case BinaryOpNode.Type.MUL:
					if self._isValueNodeTree(div.right):
						# (AnyA * AnyB) / Value == (AnyA / Value) * AnyB
						left = BinaryOpNode(BinaryOpNode.Type.DIV, div.left.left, div.right)
						right = div.left.right
						op = BinaryOpNode(BinaryOpNode.Type.MUL, left, right)
						return cast(ExpressionNode, op.accept(self))
				case _:
					pass

		if isinstance(div.right, UnaryOpNode):
			match div.right.op:
				case UnaryOpNode.Type.NEG:
					# Any / (- Any) == (- Any) / Any
					div.left = UnaryOpNode(UnaryOpNode.Type.NEG, div.left)
					div.right = div.right.value
					return cast(ExpressionNode, div.accept(self))
				case _:
					pass

		if isinstance(div.right, BinaryOpNode):
			match div.right.op:
				case BinaryOpNode.Type.DIV:
					# AnyA / (AnyB / AnyC) == (AnyA * AnyC) / AnyB
					left = BinaryOpNode(BinaryOpNode.Type.MUL, div.left, div.right.right)
					right = div.right.left
					op = BinaryOpNode(BinaryOpNode.Type.DIV, left, right)
					return cast(ExpressionNode, op.accept(self))
				case _:
					pass

		return div

	def _mulMat(self, mulmat: BinaryOpNode) -> ExpressionNode:
		return mulmat

	def _mod(self, mod: BinaryOpNode) -> ExpressionNode:
		return mod

	def _pow(self, pow: BinaryOpNode) -> ExpressionNode:
		return pow

	def _neg(self, neg: UnaryOpNode) -> ExpressionNode:

		var = self._getVariableParams(neg.value)

		if var is not None:
			# - Var == -1 * Var
			left = UnaryOpNode(UnaryOpNode.Type.NEG, var['factor'])
			right = BinaryOpNode(BinaryOpNode.Type.POW, var['variable'], var['exponent'])
			op = BinaryOpNode(BinaryOpNode.Type.MUL, left, right)
			return cast(ExpressionNode, op.accept(self))

		if isinstance(neg.value, UnaryOpNode):
			match neg.value.op:
				case UnaryOpNode.Type.NEG:
					# - (- Any) == Any
					expr = neg.value.value
					return cast(ExpressionNode, expr.accept(self))
				case _:
					pass

		if isinstance(neg.value, BinaryOpNode):
			match neg.value.op:
				case BinaryOpNode.Type.ADD:
					# - (Any + Any) == (- Any) - Any
					neg.value.left = UnaryOpNode(UnaryOpNode.Type.NEG, neg.value.left)
					neg.value.op = BinaryOpNode.Type.SUB
					return cast(ExpressionNode, neg.value.accept(self))
				case BinaryOpNode.Type.SUB:
					# - (Any - Any) == (- Any) + Any
					neg.value.left = UnaryOpNode(UnaryOpNode.Type.NEG, neg.value.left)
					neg.value.op = BinaryOpNode.Type.ADD
					return cast(ExpressionNode, neg.value.accept(self))
				case BinaryOpNode.Type.MUL:
					# - (Any * Any) == (- Any) * Any
					neg.value.left = UnaryOpNode(UnaryOpNode.Type.NEG, neg.value.left)
					return cast(ExpressionNode, neg.value.accept(self))
				case BinaryOpNode.Type.DIV:
					# - (Any / Any) == (- Any) / Any
					neg.value.left = UnaryOpNode(UnaryOpNode.Type.NEG, neg.value.left)
					return cast(ExpressionNode, neg.value.accept(self))
				case _:
					pass

		return neg

	# - Checkers & Converters --------------------------------------------------
	def _getVariableParams(self, expr: ExpressionNode) -> VariableParamsType|None:
		factor = None
		variable = None
		exponent = None

		if isinstance(expr, VariableCallNode):
			# Var
			factor = NumberNode(Number.identity())
			variable = expr
			exponent = NumberNode(Number.identity())

		if isinstance(expr, BinaryOpNode):
			match expr.op:
				case BinaryOpNode.Type.POW:
					if isinstance(expr.left, VariableCallNode):
						# Var ^ Any
						factor = NumberNode(Number.identity())
						variable = expr.left
						exponent = expr.right

				case BinaryOpNode.Type.MUL:
					if isinstance(expr.right, VariableCallNode):
						# Any * Var
						factor = expr.left
						variable = expr.right
						exponent = NumberNode(Number.identity())

					if isinstance(expr.right, BinaryOpNode):
						match expr.right.op:
							case BinaryOpNode.Type.POW:
								if isinstance(expr.right.left, VariableCallNode):
									# Any * Var ^ Any
									factor = expr.left
									variable = expr.right.left
									exponent = expr.right.right
							case _:
								pass
				case _:
					pass

		if factor is None or variable is None or exponent is None:
			return None

		return { 'factor': factor, 'variable': variable, 'exponent': exponent }

	def _isContaningVar(self, expr: ExpressionNode, name: str) -> bool:
		if isinstance(expr, BinaryOpNode):
			match expr.op:
				case BinaryOpNode.Type.ADD|BinaryOpNode.Type.SUB|BinaryOpNode.Type.MUL|BinaryOpNode.Type.DIV:
					left = self._isContaningVar(expr.left, name)
					right = self._isContaningVar(expr.right, name)
					return left or right
				case BinaryOpNode.Type.POW:
					return self._isContaningVar(expr.left, name)
				case _:
					return False

		if isinstance(expr, UnaryOpNode):
			return self._isContaningVar(expr.value, name)

		if isinstance(expr, VariableCallNode):
			return expr.name == name

		return False

	def _replaceVariables(self, expr: ExpressionNode) -> Node:
		if isinstance(expr, BinaryOpNode):
			expr.left = cast(ExpressionNode, self._replaceVariables(expr.left))
			expr.right = cast(ExpressionNode, self._replaceVariables(expr.right))
			return expr

		if isinstance(expr, UnaryOpNode):
			expr.value = cast(ExpressionNode, self._replaceVariables(expr.value))
			return expr

		if isinstance(expr, VariableCallNode):
			try:
				return self._context.getVariable(expr.name).clone()
			except UnknownVariable:
				return expr

		if isinstance(expr, FunctionCallNode):
			expr.parameter = cast(ExpressionNode, self._replaceVariables(expr.parameter))
			return expr

		return expr

	def _isValueNodeTree(self, root: ExpressionNode) -> bool:
		if isinstance(root, BinaryOpNode):
			left = self._isValueNodeTree(root.left)
			right = self._isValueNodeTree(root.right)
			return left and right

		if isinstance(root, UnaryOpNode):
			value = self._isValueNodeTree(root.value)
			return value

		if isinstance(root, ValueNode):
			return True

		return False

	def _isNumberAndLowerThan(self, left: ExpressionNode, right: ExpressionNode) -> bool:
		if isinstance(left, NumberNode):
			if isinstance(right, NumberNode):
				return left.value.toFloat() < right.value.toFloat()
			return True

		if isinstance(right, NumberNode):
			return False
		return True
