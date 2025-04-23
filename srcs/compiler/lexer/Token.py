from enum import Enum, unique, auto

class Token:
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Types ------------------------------------------------------------------
	@unique
	class Type(Enum):
		# Literals
		NUMBER     = auto() # [0-9]
		IDENTIFIER = auto() # [a-zA-Z]
		# Operators
		ADD        = auto() # +
		SUB        = auto() # -
		MUL        = auto() # *
		POW        = auto() # ^
		EQUAL      = auto() # =
		# Specials
		INVALID    = auto()
		END        = auto()

	# - Constructor ------------------------------------------------------------
	def __init__(self, type: Type, value: str|None = None) -> None:
		self._type = type
		self._value = value

	# - Getters / Setters ------------------------------------------------------
	@property
	def type(self) -> Type:
		return self._type

	@property
	def value(self) -> str|None:
		return self._value

	# - Overloads --------------------------------------------------------------
	def __repr__(self):
		return f"{self.type.name}{'('+self.value+')' if self.value != None else '' }"

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_type: Type
	_value: str|None = None
