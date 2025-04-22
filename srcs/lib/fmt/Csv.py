from __future__ import annotations
from typing import TypeAlias

import csv

from lib.io.File import File


#
# Csv
#
Csv: TypeAlias = list[list[str|int|float|bool|None]]

#
# CsvFile
#
class CsvFile(File[Csv]):

	_path: str
	_content: Csv

	def __init__(self, path: str):
		self._path = path

	def load(self) -> CsvFile:
		with open(self._path, mode='r', newline='') as f:
			self._content = list(csv.reader(f))
		return self

	def save(self) -> CsvFile:
		with open(self._path, mode='w', newline='') as f:
			csv.writer(f).writerows(self._content)
		return self

	def get_content(self) -> Csv:
		return self._content

	def set_content(self, content: Csv) -> CsvFile:
		self._content = content
		return self
