import readline
from enum import Enum, unique

class Console:
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Statics ----------------------------------------------------------------
	@unique
	class Color(Enum):
		RESET   = '\033[0m'
		# Thin
		BLACK   = '\033[30m'
		WHITE   = '\033[37m'
		RED     = '\033[31m'
		GREEN   = '\033[32m'
		BLUE    = '\033[34m'
		YELLOW  = '\033[33m'
		CYAN    = '\033[36m'
		MAGENTA = '\033[35m'
		# Bold
		BOLD_BLACK   = '\033[01m\033[30m'
		BOLD_WHITE   = '\033[01m\033[37m'
		BOLD_RED     = '\033[01m\033[31m'
		BOLD_GREEN   = '\033[01m\033[32m'
		BOLD_BLUE    = '\033[01m\033[34m'
		BOLD_YELLOW  = '\033[01m\033[33m'
		BOLD_CYAN    = '\033[01m\033[36m'
		BOLD_MAGENTA = '\033[01m\033[35m'

	@staticmethod
	def input(prefix: str = "", color: Color = Color.WHITE) -> str:
		colored_str = Console._colorize(prefix, color)
		return input(colored_str)

	@staticmethod
	def output(txt: str, color: Color = Color.WHITE) -> None:
		colored_str = Console._colorize(txt, color)
		print(colored_str, end='')

	# ==========================================================================
	# Public
	# ==========================================================================
	# - Statics ----------------------------------------------------------------
	@staticmethod
	def _colorize(txt: str, color: Color) -> str:
		return f"{color.value}{txt}{Console.Color.RESET.value}"
