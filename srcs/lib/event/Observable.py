from __future__ import annotations
from typing import Generic, TypeVar, Callable, TypeAlias
from abc import ABC


#
# Observable
#
T = TypeVar('T')

EventName: TypeAlias = str
EventCallback: TypeAlias = Callable[[T], None]

class Observable(ABC, Generic[T]):

	_callbacks: dict[EventName, list[EventCallback]]

	def __init__(self):
		self._callbacks = {}

	def on(self, name: EventName, cb: EventCallback) -> Observable:
		self._callbacks[name] = self._callbacks.get(name, []) + [cb]
		return self

	def emit(self, name: EventName, payload: T) -> Observable:
		for cb in self._callbacks.get(name, []):
			cb(payload)
		return self
