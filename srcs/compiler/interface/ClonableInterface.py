from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Any

class ClonableInterface(ABC):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Methods ----------------------------------------------------------------
	@abstractmethod
	def clone(self) -> Any:
		raise NotImplementedError
