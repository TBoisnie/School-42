from __future__ import annotations

import matplotlib.pyplot as plt

from .Window import GridWindow


#
# UserInterface (UI)
#
class UserInterface:

	def __init__(self):
		pass

	def set_font(self, size: int) -> UserInterface:
		plt.rcParams.update({ 'font.size': size })
		return self

	def create_grid_window(self, rows: int = 1, columns: int = 1, title: str = None) -> GridWindow:
		return GridWindow(rows, columns, title)

	def show(self) -> UserInterface:
		plt.show()
		return self
