from __future__ import annotations
from typing import cast

from compiler.interpreter.Interpreter import Interpreter
from compiler.interpreter.EquationSolver import EquationSolver
from compiler.lexer.Lexer import Lexer
from compiler.parser.Parser import Parser
from compiler.optimizer.Optimizer import Optimizer
from compiler.parser.Node import *
from utilities.Console import Console

class Compiler:
	# ==========================================================================
	# Public
	# ==========================================================================
	# - Constructor ------------------------------------------------------------
	def __init__(self):
		self._lexer = Lexer()
		self._parser = Parser()
		self._optimizer = Optimizer()
		self._interpreter = Interpreter()

	# - Methods ----------------------------------------------------------------
	def execute(self, src_str: str) -> None:
		tokens_itr = self._lexer.tokenize(src_str)
		# Console.output(f"Parser:      {list(tokens_itr)}\n", Console.Color.BOLD_WHITE)
		ast = self._parser.build(tokens_itr)
		# Console.output(f"Parser:      {ast}\n", Console.Color.BOLD_BLUE)
		ast = self._optimizer.optimize(ast)
		# Console.output(f"Optimizer:   {ast}\n", Console.Color.BOLD_GREEN)
		ast = self._interpreter.run(ast)
		# Console.output(f"Interpreter: {ast}\n", Console.Color.BOLD_YELLOW)

		solver = EquationSolver(cast(EquationNode, ast))
		solutions = solver.solve()

		Console.output(f"Reduced form: {solver.reduceForm()}\n", Console.Color.BLUE)
		Console.output(f"Polynomial degree: {solver.degree}\n", Console.Color.MAGENTA)

		if solutions is None:
			if solver.degree <= 2:
				Console.output(f"No solution.\n", Console.Color.YELLOW)
			else:
				Console.output(f"The polynomial degree is strictly greater than 2, I can't solve.\n", Console.Color.YELLOW)
			return

		if solver.degree == 0:
			Console.output(f"The equality is: { len(solutions) != 0 }\n", Console.Color.GREEN)
			return

		if solver.degree == 1:
			solutions = 'Any x from |R.' if len(solutions) == 0 else solutions[0]
			Console.output(f"The solution is:\n{ solutions }\n", Console.Color.GREEN)
			return

		if solver.degree == 2:
			delta = cast(Number, solver.delta).toFloat()
			sign = 'positive' if delta > 0.0 else 'negative'

			Console.output(f"Discriminant: Strictly { sign } ({ delta })\n", Console.Color.MAGENTA)

			if delta == 0.0:
				Console.output(f"The solution is:\n{ solutions[0] }\n", Console.Color.GREEN)
			else:
				Console.output(f"The solutions are:\n{ solutions[0] }\n{ solutions[1] }\n", Console.Color.GREEN)
			return


	# ==========================================================================
	# Private
	# ==========================================================================
	# - Properties -------------------------------------------------------------
	_lexer: Lexer
	_parser: Parser
	_optimizer: Optimizer
	_interpreter: Interpreter
