from __future__ import annotations
from typing import Generic, TypeVar
from abc import abstractmethod


#
# Storage
#
K = TypeVar('K')
V = TypeVar('V')

class Storage(Generic[K, V]):

	@abstractmethod
	def get(self, key: K, default: V) -> V:
		pass

	@abstractmethod
	def set(self, key: K, value: V) -> Storage:
		pass

	@abstractmethod
	def push(self, key: K, value: V) -> Storage:
		pass

#
# InMemoryStorage
#
class InMemoryStorage(Generic[K, V], Storage[K, V]):

	_storage: dict[K, V]

	def __init__(self):
		self._storage = {}

	def get(self, key: K, default: V = None) -> V|None:
		return self._storage.get(key, default)

	def set(self, key: K, value: V) -> InMemoryStorage:
		self._storage[key] = value
		return self

	def push(self, key: K, value: V) -> InMemoryStorage:
		self.set(key, self.get(key, []) + [value])
		return self
