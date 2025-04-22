from __future__ import annotations
from typing import Literal

import numpy as np
import matplotlib.pyplot as plt


#
# Graph
#
class Graph:
	pass

#
# MultiGraph
#
class MultiGraph(Graph):

	_axe: plt.Axes

	def __init__(self, axe: plt.Axes):
		self._axe = axe

	def set_title(self, title: str) -> MultiGraph:
		self._axe.set_title(title)
		return self

	def set_label(self, axe: Literal['x', 'y'], name: str) -> MultiGraph:
		if axe == 'x':
			self._axe.set_xlabel(name)
		else:
			self._axe.set_ylabel(name)
		return self

	def set_ticks(self, axe: Literal['x', 'y'], label: bool = True) -> MultiGraph:
		if axe == 'y':
			self._axe.tick_params(labelleft=label)
		else:
			self._axe.tick_params(labelbottom=label)
		return self

	def set_spines(self, pos: Literal['top', 'right'], visible: bool = True) -> MultiGraph:
		self._axe.spines[pos].set_visible(visible)
		return self

	def enable_legends(self) -> MultiGraph:
		self._axe.legend()
		return self

	def add_hist(self, values: list, label: str = None, alpha: float = 0.8):
		self._axe.hist(values, label=label, histtype='bar', alpha=alpha)
		return self

	def add_line(self, x: list = None, y: list = [], label: str = None, alpha: float = 0.8) -> MultiGraph:
		self._axe.plot(x if x is not None else range(len(y)), y, label=label, alpha=alpha)
		return self

	def add_bars(self, x: list = None, y: list = [], label: list|str = None) -> MultiGraph:
		self._axe.bar(x if x is not None else range(len(y)), y, label=label)
		return self

	def add_scatter(self, x: list, y: list, sizes: list = None, label: str = None, alpha: float = 0.5) -> MultiGraph:
		sizes = sizes if sizes is not None else 1
		self._axe.scatter(x, y, s=sizes, label=label, alpha=alpha)
		return self

	def add_stacked_bars(self, x: list = None, y: list[dict] = []):
		assert len(y) > 0, \
			"UI::MultiGraph::AddStackedBars: `y` can't be empty."

		if x is None:
			x = range(len(y))

		stats = { k: [ d[k] for d in y ] for k in y[0] }
		bottoms = np.zeros(len(x))

		for label, values in stats.items():
			bar = self._axe.bar(x, values, width=0.8, label=label.replace('_', ' ').capitalize(), bottom=bottoms)
			bottoms += values
			self._axe.bar_label(bar, label_type='center')

		return self
