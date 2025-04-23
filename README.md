# 42 - Compiler - Computor V1

Implementation in `python` of an equation interpreter and solver.

## Requirements

- [Python 3](https://www.python.org/)

## Getting Started

1. Execute

	```sh
	# Run
	python3 ./srcs/computor.py
	```

## Example

```sh
python3 ./srcs/computor.py

--------------------------------------------------------------------------------
---- ComputorV1 ----------------------------------------------------------------
--------------------------------------------------------------------------------
> 8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0
Reduced form: -5.6X^3+0X^2-6X+5 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve.

> 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0
Reduced form: -9.3X^2+4X+4 = 0
Polynomial degree: 2
Discriminant: Strictly positive (164.8)
The solutions are:
0.905239
-0.475131

> 5 * X^0 + 4 * X^1 = 4 * X^0
Reduced form: 4X+1 = 0
Polynomial degree: 1
The solution is:
-0.25

> 1 * X^0 = 1 * X^0
Reduced form: 0 = 0
Polynomial degree: 0
The equality is: True

> 8 - 6x + 5.6x^3 = 3
Reduced form: 5.6x^3-6x+5 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve.

> 5 + 4x - 9.3x^2 = 1
Reduced form: -9.3x^2+4x+4 = 0
Polynomial degree: 2
Discriminant: Strictly positive (164.8)
The solutions are:
0.905239
-0.475131

> 5 + 4x = 4
Reduced form: 4x+1 = 0
Polynomial degree: 1
The solution is:
-0.25

> 1 = 1
Reduced form: 0 = 0
Polynomial degree: 0
The equality is: True

> 8 - 6x + x^3 = x^3
Reduced form: 0x^3-6x+8 = 0
Polynomial degree: 1
The solution is:
-4_-3

> 0x^2+1=0
Reduced form: 0x^2+1 = 0
Polynomial degree: 0
The equality is: False

> 4 + 5 =
Compiler::Parser::InvalidSyntax: Unexpected 'END', expected 'IDENTIFIER | NUMBER'.

> 4 + = 5
Compiler::Parser::InvalidSyntax: Unexpected 'EQUAL', expected 'IDENTIFIER | NUMBER'.

> 4 5 = -1
Compiler::Parser::InvalidSyntax: Unexpected 'NUMBER(5)', expected 'EQUAL'.
```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
