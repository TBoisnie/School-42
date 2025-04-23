from __future__ import annotations
from abc import ABC, abstractmethod

class RepresentableInterface(ABC):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Overloads --------------------------------------------------------------
	@abstractmethod
	def __repr__(self) -> str:
		raise NotImplementedError
