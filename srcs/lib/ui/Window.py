from __future__ import annotations

import matplotlib.pyplot as plt
import matplotlib.gridspec as gs

from .Graph import MultiGraph


#
# Window
#
class Window:
	pass

#
# GridWindow
#
class GridWindow(Window):

	_rows: int
	_columns: int

	_figure: plt.Figure
	_spec: gs.GridSpec

	def __init__(self, rows: int = 1, columns: int = 1, title: str = None):
		assert rows > 0, \
			"Window::GridWindow: `rows` must be more than 1."
		assert columns > 0, \
			"Window::GridWindow: `columns` must be more than 1."

		self._rows = rows
		self._columns = columns

		self._figure = plt.figure(title, layout='constrained', figsize=(16, 9))
		self._spec = gs.GridSpec(rows, columns, figure=self._figure)

	@property
	def rows(self) -> int:
		return self._rows

	@property
	def columns(self) -> int:
		return self._columns

	def enable_legends(self, labels: list) -> GridWindow:
		self._figure.legend(labels, loc="outside center right")
		return self

	def create_multigraph(self, row: int = 0, column: int = 0, row_span: int = 1, column_span: int = 1) -> MultiGraph:
		ax = self._figure.add_subplot(self._spec[row:row+row_span, column:column+column_span])
		return MultiGraph(ax)
