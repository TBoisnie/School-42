from __future__ import annotations
from abc import abstractmethod
from typing import Any

from compiler.interface.EqualableInterface import EqualableInterface

class ComparableInterface(EqualableInterface):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Overloads --------------------------------------------------------------
	@abstractmethod
	def __lt__(self, other: Any) -> bool:
		raise NotImplementedError

	@abstractmethod
	def __le__(self, other: Any) -> bool:
		raise NotImplementedError

	@abstractmethod
	def __gt__(self, other: Any) -> bool:
		raise NotImplementedError

	@abstractmethod
	def __ge__(self, other: Any) -> bool:
		raise NotImplementedError
