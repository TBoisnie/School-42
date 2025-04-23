from compiler.parser.Node import *

class InterpreterError(Exception):
	def __init__(self, message: str):
		super().__init__(f"Interpreter::{message}")

class NotImplementedBuiltIn(InterpreterError):
	def __init__(self, fun_name: str):
		super().__init__(f"NotImplementedBuiltIn: {fun_name}")

class UnsupportedOperator(InterpreterError):
	def __init__(self, op: BinaryOpNode.Type|UnaryOpNode.Type, info: str):
		super().__init__(f"UnsupportedOperator::{op.name.capitalize()}: {info}")

class InvalidEquationFormat(InterpreterError):
	def __init__(self, info: str):
		super().__init__(f"InvalidEquationFormat::{info}")

class InvalidFunctionParameter(InterpreterError):
	def __init__(self, fun_name: str, info: str):
		super().__init__(f"InvalidFunctionParameter::{fun_name}: {info}")
