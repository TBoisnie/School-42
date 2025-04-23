#!/usr/bin/env python3

from compiler.Compiler import Compiler
from utilities.Console import Console
from Test import Test

if __name__ == "__main__":
	Console.output(f"{'-' * 80}\n", Console.Color.CYAN)
	Console.output(f"{'-' * 4 } ComputorV2 {'-' * 64}\n", Console.Color.CYAN)
	Console.output(f"{'-' * 80}\n", Console.Color.CYAN)

	# - Boot -------------------------------------------------------------------
	# Generator
	boot = Compiler()

	# operands = [ '-2.5', '5', 'i', 'x', 'y', 'z' ]
	# operators = [ '+', '-', '*', '/', '%' ]

	tests = Test.defined()
	tests.clear()
	# tests = Test.generate(operands, operators)

	for test in tests:
		Console.output(f"> ", Console.Color.CYAN)
		Console.output(f"{test}\n")
		try:
			boot.execute(test)
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

		match source_str:
			case 'exit':
				break
			case 'help':
				Console.output(f"Command list:\n", Console.Color.CYAN)
				Console.output(f"-  help\n", Console.Color.CYAN)
				Console.output(f"-  exit\n", Console.Color.CYAN)
				Console.output(f"-  list-variables\n", Console.Color.CYAN)
				Console.output(f"-  list-functions\n", Console.Color.CYAN)
				Console.output(f"-  list-builtin\n", Console.Color.CYAN)
			case 'list-variables':
				Console.output(f"{compiler.context.variables}\n", Console.Color.MAGENTA)
			case 'list-functions':
				Console.output(f"{compiler.context.functions}\n", Console.Color.YELLOW)
			case 'list-builtin':
				Console.output(f"{compiler.context.builtin}\n", Console.Color.GREEN)
			case _:
				try:
					compiler.execute(source_str)
				except Exception as e:
					Console.output(f"Compiler::{e}\n", Console.Color.RED)

		Console.output(f"\n")
