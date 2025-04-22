from __future__ import annotations
from typing import Generic, TypeVar
from abc import abstractmethod


#
# File
#
T = TypeVar('T')

class File(Generic[T]):

	@abstractmethod
	def load(self) -> File:
		pass

	@abstractmethod
	def save(self) -> File:
		pass

	@abstractmethod
	def get_content(self) -> T:
		pass

	@abstractmethod
	def set_content(self, content: T) -> File:
		pass
