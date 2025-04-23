#!/usr/bin/env python3
from sys import argv

from compiler.Compiler import Compiler
from utilities.Console import Console

def main():
	# Single run invalid
	if len(argv) > 2:
		Console.output(f"Single run usage: ./computor \"4x + 5 = 2x^2\"\n", Console.Color.RED)
		return

	# Single run
	if len(argv) == 2:
		compiler = Compiler()

		try:
			compiler.execute(argv[1])
		except Exception as e:
			Console.output(f"Compiler::{e}\n", Console.Color.RED)

		Console.output(f"\n")
		return

	# Endless run
	Console.output(f"{'-' * 80}\n", Console.Color.BOLD_YELLOW)
	Console.output(f"{'-' * 4 } ComputorV1 {'-' * 64}\n", Console.Color.BOLD_YELLOW)
	Console.output(f"{'-' * 80}\n", Console.Color.BOLD_YELLOW)

	# - Boot -------------------------------------------------------------------
	ALIAS = {
		'test_equation_normal_form_3': "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0",
		'test_equation_normal_form_2': "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0",
		'test_equation_normal_form_1': "5 * X^0 + 4 * X^1 = 4 * X^0",
		'test_equation_normal_form_0': "1 * X^0 = 1 * X^0",
		'test_equation_free_form_3': "8 - 6x + 5.6x^3 = 3",
		'test_equation_free_form_2': "5 + 4x - 9.3x^2 = 1",
		'test_equation_free_form_1': "5 + 4x = 4",
		'test_equation_free_form_0': "1 = 1",
		'test_equation_free_form_3_with_null_factor': "8 - 6x + x^3 = x^3",
		'test_equation_free_form_no_solution': "0x^2+1=0",
		'test_error_empty_right': "4 + 5 =",
		'test_error_missing_operand': "4 + = 5",
		'test_error_missing_operator': "4 5 = -1",
	}

	boot = Compiler()

	for alias in ALIAS.values():
		Console.output(f"> ", Console.Color.CYAN)
		Console.output(f"{alias}\n")
		try:
			boot.execute(alias)
		except Exception as e:
			Console.output(f"Compiler::{e}\n", Console.Color.RED)
		Console.output(f"\n")

	del boot

	# - Main -------------------------------------------------------------------
	compiler = Compiler()

	while True:
		source_str = Console.input("> ", Console.Color.CYAN).strip()

		if not source_str:
			continue

		if source_str == 'exit':
			break
		if source_str == 'help':
			Console.output(f"Command list:\n", Console.Color.CYAN)
			Console.output(f"-  help\n", Console.Color.CYAN)
			Console.output(f"-  exit\n", Console.Color.CYAN)
		else:
			try:
				compiler.execute(source_str)
			except Exception as e:
				Console.output(f"Compiler::{e}\n", Console.Color.RED)

		Console.output(f"\n")


if __name__ == "__main__":
	main()
