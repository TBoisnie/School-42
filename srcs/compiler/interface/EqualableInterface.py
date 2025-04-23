from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Any

class EqualableInterface(ABC):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Overloads --------------------------------------------------------------
	@abstractmethod
	def __eq__(self, other: Any) -> bool:
		raise NotImplementedError
