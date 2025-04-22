from __future__ import annotations
from enum import IntEnum

import numpy as np


#
# DataSet
#
class DataSet:

	class Axis(IntEnum):
		ROW = 0
		COLUMN = 1

	_header: bool # Column ID
	_index: bool # Row ID
	_data: np.ndarray

	def __init__(self, data: np.ndarray, header: bool = False, index: bool = False):
		self._data = data
		self._header = header
		self._index = index

	@property
	def headers(self) -> np.ndarray:
		return self._data[0] if self._header else np.array([])

	@property
	def indexes(self) -> np.ndarray:
		return self._data[:, 0] if self._index else np.array([])

	@property
	def content(self) -> np.ndarray:
		return self._data[self._header:, self._index:]

	@property
	def shape(self) -> tuple[int, int]:
		return (self._data.shape[0] - self._header, self._data.shape[1] - self._index)

	@property
	def raw_data(self) -> np.ndarray:
		return self._data

	def set_type(self, to_type) -> DataSet:
		self._data = self._data.astype(to_type)
		return self

	def add(self, values: np.ndarray, position: int = None, axis: Axis = Axis.ROW) -> DataSet:
		position = position if position is not None else self._data.shape[axis]
		match axis:
			case DataSet.Axis.ROW:
				self._data = np.r_[self._data[:position], [values], self._data[position:]]
			case DataSet.Axis.COLUMN:
				self._data = np.c_[self._data[:, :position], values, self._data[:, position:]]
		return self

	def remove(self, position: list[int]|int, axis: Axis = Axis.ROW) -> DataSet:
		if isinstance(position, int):
			position = [position]
		match axis:
			case DataSet.Axis.ROW:
				for i in position:
					self._data = np.delete(self._data, i + 1 if self._header else i, axis)
			case DataSet.Axis.COLUMN:
				for i in position:
					self._data = np.delete(self._data, i + 1 if self._index else i, axis)
		return self

	def swap(self, i: int, j: int, axis: Axis = Axis.ROW) -> DataSet:
		match axis:
			case DataSet.Axis.ROW:
				self._data[[i, j], :] = self._data[[j, i], :]
			case DataSet.Axis.COLUMN:
				self._data[:, [i, j]] = self._data[:, [j, i]]
		return self

	def shuffle(self, axis: Axis = Axis.ROW) -> DataSet:
		match axis:
			case DataSet.Axis.ROW:
				rows = self._data[self._header:, :]
				np.random.default_rng().shuffle(rows, axis)
				self._data[self._header:, :] = rows
			case DataSet.Axis.COLUMN:
				columns = self._data[:, self._index:]
				np.random.default_rng().shuffle(columns, axis)
				self._data[:, self._index:] = columns
		return self

	def normalize(self, axis: Axis = Axis.COLUMN) -> DataSet:
		# Reverse axis makes more sense from the name
		axis = [DataSet.Axis.COLUMN, DataSet.Axis.ROW][axis]
		content = self.content.astype(float)
		min = np.min(content, axis, keepdims=True)
		max = np.max(content, axis, keepdims=True)
		self._data[self._header:, self._index:] = (content - min) / (max - min)
		return self

	def split(self, percent: float = 50, position: int = None, axis: Axis = Axis.ROW) -> tuple[DataSet, DataSet]:
		match axis:
			case DataSet.Axis.ROW:
				limit = position if position is not None else int((self._data.shape[axis] - self._header) / 100. * percent)
				data_a = np.r_[self._data[:self._header], self._data[self._header:limit]]
				data_b = np.r_[self._data[:self._header], self._data[limit:]]
			case DataSet.Axis.COLUMN:
				limit = position if position is not None else int((self._data.shape[axis] - self._index) / 100. * percent)
				data_a = np.c_[self._data[:, :self._index], self._data[:, self._index:limit]]
				data_b = np.c_[self._data[:, :self._index], self._data[:, limit:]]
		return (
			DataSet(data_a, self._header, self._index),
			DataSet(data_b, self._header, self._index),
		)
