class ContextError(Exception):
	def __init__(self, message: str):
		super().__init__(f"Context::{message}")

class UnknownVariable(ContextError):
	def __init__(self, name: str):
		super().__init__(f"UnknownVariable: {name}")

class UnknownFunction(ContextError):
	def __init__(self, name: str):
		super().__init__(f"UnknownFunction: {name}")

class ReservedVariableName(ContextError):
	def __init__(self, name: str):
		super().__init__(f"ReservedVariableName: {name}.")

class ReservedFunctionName(ContextError):
	def __init__(self, name: str):
		super().__init__(f"ReservedFunctionName: {name}.")
