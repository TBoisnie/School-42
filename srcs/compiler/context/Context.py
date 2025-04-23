from __future__ import annotations
from typing import TypedDict, Tuple

from compiler.context.BuiltIn import BuiltIn
from compiler.context.Error import UnknownVariable, UnknownFunction, ReservedVariableName, ReservedFunctionName
from compiler.interface.ClonableInterface import ClonableInterface
from compiler.parser.Node import *

VariableDef = ExpressionNode
FunctionDef = TypedDict('FunctionDef', { 'arg': str, 'value': ExpressionNode })

class Context(ClonableInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self):
		self._variables = {}
		self._functions = {}

		self._loadVariables()

	# - Checkers & Converters --------------------------------------------------
	def isReservedVariableName(self, name: str) -> bool:
		return name.lower() in BuiltIn.getVariablesList()

	def isReservedFunctionName(self, name: str) -> bool:
		return name.lower() in BuiltIn.getFunctionsList()

	# - Getters & Setters ------------------------------------------------------
	def getVariable(self, name: str) -> VariableDef:
		try:
			return self._variables[name.lower()]
		except KeyError:
			raise UnknownVariable(name)

	def getFunction(self, name: str) -> FunctionDef:
		try:
			return self._functions[name.lower()]
		except KeyError:
			raise UnknownFunction(name)

	@property
	def variables(self) -> dict[str, VariableDef]:
		return self._variables

	@property
	def functions(self) -> dict[str, FunctionDef]:
		return self._functions

	@property
	def builtin(self) -> Tuple[str, ...]:
		return BuiltIn.getFunctionsList()

	def setVariable(self, name: str, value: ExpressionNode) -> None:
		if self.isReservedVariableName(name):
			raise ReservedVariableName(name)

		self._variables[name.lower()] = value

	def setFunction(self, name: str, arg: str, value: ExpressionNode) -> None:
		if self.isReservedFunctionName(name):
			raise ReservedFunctionName(name)

		self._functions[name.lower()] = { 'arg': arg, 'value': value }

	# - Interface --------------------------------------------------------------
	def clone(self) -> Context:
		ctx = Context()
		ctx._variables = { k: v.clone() for k, v in self.variables.items() }
		ctx._functions = { k: { 'arg': v['arg'], 'value': v['value'].clone() } for k, v in self.functions.items() }
		return ctx

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_variables: dict[str, VariableDef]
	_functions: dict[str, FunctionDef]

	# - Methods ----------------------------------------------------------------
	def _loadVariables(self) -> None:
		self._variables['i']  = ComplexNode(BuiltIn.I)
		self._variables['e']  = NumberNode(BuiltIn.E)
		self._variables['pi'] = NumberNode(BuiltIn.PI)
