from typing import Iterator, Iterable, TypeVar, Generic

T = TypeVar('T')

class Pickator(Iterable[T], Generic[T]):
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self, iterable: Iterable[T]):
		self._itr = iter(iterable)
		self.consume()

	# - Methods ----------------------------------------------------------------
	def pick(self) -> T|None:
		return self._current

	def consume(self) -> T|None:
		self._advance()
		return self._current

	# - Overloads --------------------------------------------------------------
	def __iter__(self):
		return self

	def __next__(self) -> T:
		current = self._current

		self._advance()

		if current is not None:
			return current

		raise StopIteration

	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_current: T|None
	_itr: Iterator[T]

	# - Methods ----------------------------------------------------------------
	def _advance(self) -> None:
		try:
			self._current = next(self._itr)
		except StopIteration:
			self._current = None
