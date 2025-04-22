from __future__ import annotations
from typing import TypeAlias
from abc import abstractmethod

import json


#
# Json
#
Json: TypeAlias = dict|list|str|int|float|None

#
# Jsonable
#
class Jsonable:

	@abstractmethod
	def to_json(self) -> Json:
		pass

	@abstractmethod
	def from_json(self):
		pass

#
# JsonFile
#
class JsonFile:

	_path: str
	_content: Json

	def __init__(self, path: str):
		self._path = path

	def load(self) -> JsonFile:
		with open(self._path, mode='r', newline='') as f:
			self._content = json.load(f)
		return self

	def save(self) -> JsonFile:
		with open(self._path, mode='w', newline='') as f:
			json.dump(self._content, f, indent=2)
		return self

	def get_content(self) -> Json:
		return self._content

	def set_content(self, content: Json) -> JsonFile:
		self._content = content
		return self
