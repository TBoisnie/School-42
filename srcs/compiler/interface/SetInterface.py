from __future__ import annotations
from abc import abstractmethod
from typing import Any

from compiler.interface.ClonableInterface import ClonableInterface
from compiler.interface.RepresentableInterface import RepresentableInterface

class SetInterface(ClonableInterface, RepresentableInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Overloads --------------------------------------------------------------
	@abstractmethod
	def __add__(self, other: Any) -> Any:
		raise NotImplementedError

	@abstractmethod
	def __sub__(self, other: Any) -> Any:
		raise NotImplementedError

	@abstractmethod
	def __mul__(self, other: Any) -> Any:
		raise NotImplementedError

	@abstractmethod
	def __truediv__(self, other: Any) -> Any:
		raise NotImplementedError

	@abstractmethod
	def __pow__(self, exp: Any) -> Any:
		raise NotImplementedError

	@abstractmethod
	def __neg__(self) -> Any:
		raise NotImplementedError

	# - Statics ----------------------------------------------------------------
	@staticmethod
	@abstractmethod
	def null() -> Any:
		raise NotImplementedError

	@staticmethod
	@abstractmethod
	def identity() -> Any:
		raise NotImplementedError
