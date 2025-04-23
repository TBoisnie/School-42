from __future__ import annotations
from dataclasses import dataclass
from enum import Enum, unique

from compiler.interface.ClonableInterface import ClonableInterface
from compiler.interface.RepresentableInterface import RepresentableInterface
from compiler.interface.VisitorInterface import VisitorInterface, VisitableInterface
from compiler.types.Number import Number

# ==============================================================================
# Base
# ==============================================================================
class Node(VisitableInterface, ClonableInterface, RepresentableInterface):
	pass

# ==============================================================================
# Statement
# ==============================================================================
class StatementNode(Node):
	pass

# - Definitions ----------------------------------------------------------------
@dataclass
class EquationNode(StatementNode):
	left: ExpressionNode
	right: ExpressionNode

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitEquation(self)

	def clone(self):
		return type(self)(self.left.clone(), self.right.clone())

	def __repr__(self) -> str:
		return f"{self.left} = {self.right}"

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
		POW     = '^'

	op: BinaryOpNode.Type
	left: ExpressionNode
	right: ExpressionNode

	def accept(self, vtor: VisitorInterface) -> Node:
		return vtor.visitBinaryOp(self)

	def clone(self):
		return type(self)(self.op, self.left.clone(), self.right.clone())

	def __repr__(self) -> str:
		return f"({self.left} {self.op.value} {self.right})"

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
		return f"({self.op.value}{self.value})"

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
