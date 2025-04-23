from __future__ import annotations
from dataclasses import dataclass
from enum import Enum, unique

from compiler.interface.ClonableInterface import ClonableInterface
from compiler.interface.EqualableInterface import EqualableInterface
from compiler.interface.RepresentableInterface import RepresentableInterface
from compiler.interface.VisitorInterface import VisitorInterface, VisitableInterface
from compiler.types.Complex import Complex
from compiler.types.Matrix import Matrix
from compiler.types.Number import Number

# ==============================================================================
# Base
# ==============================================================================
class Node(VisitableInterface, ClonableInterface, RepresentableInterface, EqualableInterface):
	pass

# ==============================================================================
# Statement
# ==============================================================================
class StatementNode(Node):
	pass

# - Definitions ----------------------------------------------------------------
@dataclass
class VariableDefNode(StatementNode):
	name: str
	value: ExpressionNode

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitVariableDef(self)

	def clone(self):
		return type(self)(self.name, self.value.clone())

	def __repr__(self) -> str:
		return f"{self.name} = {self.value}"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, VariableDefNode):
			return False

		return (self.name == other.name and self.value == other.value)

@dataclass
class FunctionDefNode(StatementNode):
	name: str
	arg: str
	body: ExpressionNode

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitFunctionDef(self)

	def clone(self):
		return type(self)(self.name, self.arg, self.body.clone())

	def __repr__(self) -> str:
		return f"{self.name}({self.arg}) = {self.body}"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, FunctionDefNode):
			return False

		return (self.name == other.name and self.arg == other.arg and self.body == other.body)

# - Evaluation -----------------------------------------------------------------
@dataclass
class EvalNode(StatementNode):
	body: ExpressionNode

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitEval(self)

	def clone(self):
		return type(self)(self.body.clone())

	def __repr__(self) -> str:
		return f"{self.body} = ?"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, EvalNode):
			return False

		return (self.body == other.body)

@dataclass
class EquationNode(StatementNode):
	left: ExpressionNode
	right: ExpressionNode

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitEquation(self)

	def clone(self):
		return type(self)(self.left.clone(), self.right.clone())

	def __repr__(self) -> str:
		return f"{self.left} = {self.right} ?"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, EquationNode):
			return False

		return (self.left == other.left and self.right == other.right)

# ==============================================================================
# Expressions
# ==============================================================================
class ExpressionNode(Node):
	pass

# - Binary Operators -----------------------------------------------------------
@dataclass
class BinaryOpNode(ExpressionNode):
	@unique
	class Type(Enum):
		ADD     = '+'
		SUB     = '-'
		MUL     = '*'
		MUL_MAT = '**'
		DIV     = '/'
		MOD     = '%'
		POW     = '^'

	op: BinaryOpNode.Type
	left: ExpressionNode
	right: ExpressionNode

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitBinaryOp(self)

	def clone(self):
		return type(self)(self.op, self.left.clone(), self.right.clone())

	def __repr__(self) -> str:
		is_pow_one = self.op is BinaryOpNode.Type.POW \
			and isinstance(self.right, NumberNode) \
			and self.right.value == Number.identity()

		if is_pow_one:
			return f"{self.left}"

		is_mul_one = self.op is BinaryOpNode.Type.MUL \
			and isinstance(self.left, NumberNode) \
			and self.left.value == Number.identity()

		if is_mul_one:
			return f"{self.right}"

		return f"({self.left} {self.op.value} {self.right})"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, BinaryOpNode):
			return False

		return (self.op is other.op and self.left == other.left and self.right == other.right)

# - Unary Operators ------------------------------------------------------------
@dataclass
class UnaryOpNode(ExpressionNode):
	@unique
	class Type(Enum):
		NEG = '-'

	op: UnaryOpNode.Type
	value: ExpressionNode

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitUnaryOp(self)

	def clone(self):
		return type(self)(self.op, self.value.clone())

	def __repr__(self) -> str:
		is_not_expr = isinstance(self.value, ValueNode) \
			or isinstance(self.value, VariableCallNode) \
			or isinstance(self.value, FunctionCallNode)
		value = f"{self.value}" if is_not_expr else f"({self.value})"

		return f"({self.op.value}{value}"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, UnaryOpNode):
			return False

		return (self.op is other.op and self.value == other.value)

# - Calls ----------------------------------------------------------------------
@dataclass
class VariableCallNode(ExpressionNode):
	name: str

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitVariableCall(self)

	def clone(self):
		return type(self)(self.name)

	def __repr__(self) -> str:
		return f"{self.name}"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, VariableCallNode):
			return False

		return (self.name == other.name)

@dataclass
class FunctionCallNode(ExpressionNode):
	name: str
	parameter: ExpressionNode

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitFunctionCall(self)

	def clone(self):
		return type(self)(self.name, self.parameter.clone())

	def __repr__(self) -> str:
		return f"{self.name}({self.parameter})"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, FunctionCallNode):
			return False

		return (self.name == other.name and self.parameter == other.parameter)

# - Values ---------------------------------------------------------------------
class ValueNode(ExpressionNode):
	pass

@dataclass
class NumberNode(ValueNode):
	value: Number

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitNumber(self)

	def clone(self):
		return type(self)(self.value.clone())

	def __repr__(self) -> str:
		return f"{self.value}"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, NumberNode):
			return False

		return (self.value == other.value)

@dataclass
class MatrixNode(ValueNode):
	value: Matrix

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitMatrix(self)

	def clone(self):
		return type(self)(self.value.clone())

	def __repr__(self) -> str:
		return f"{self.value}"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, MatrixNode):
			return False

		return (self.value == other.value)

@dataclass
class ComplexNode(ValueNode):
	value: Complex

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitComplex(self)

	def clone(self):
		return type(self)(self.value.clone())

	def __repr__(self) -> str:
		return f"{self.value}"

	def __eq__(self, other: Node) -> bool:
		if not isinstance(other, ComplexNode):
			return False

		return (self.value == other.value)
