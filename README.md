# 42 - Compiler - Computor V2

Implementation in `python` of a math interpreter.

Features :
- Complex
- Matrix
- Builtin Variable (e, pi, i, ...)
- Builtin Function (abs, ceil, floor, transpose, trace, ...)
- Custom Variable
- Custom Function
- ...

## Requirements

- [Python 3](https://www.python.org/)

## Getting Started

1. Execute

	```sh
	# Run
	python3 ./srcs/ComputorV2.py

	--------------------------------------------------------------------------------
	---- ComputorV2 ----------------------------------------------------------------
	--------------------------------------------------------------------------------
	> help
	Command list:
	-  help
	-  exit
	-  list-variables
	-  list-functions
	-  list-builtin

	> list-variables
	{'i': i, 'e': 2.71828, 'pi': 3.14159}

	> list-functions
	{}

	> list-builtin
	('abs', 'sqrt', 'floor', 'ceil', 'rad', 'trace', 'transpose')
	```

## Example

```sh
python3 ./srcs/ComputorV2.py

--------------------------------------------------------------------------------
---- ComputorV2 ----------------------------------------------------------------
--------------------------------------------------------------------------------
> 8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0 ?
Reduced form: -5.6X^3+0X^2-6X+5 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve.

> 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0 ?
Reduced form: -9.3X^2+4X+4 = 0
Polynomial degree: 2
Discriminant: Strictly positive (164.8)
The solutions are:
0.905239
-0.475131

> 5 * X^0 + 4 * X^1 = 4 * X^0 ?
Reduced form: 4X+1 = 0
Polynomial degree: 1
The solution is:
-0.25

> 1 * X^0 = 1 * X^0 ?
Reduced form: 0 = 0
Polynomial degree: 0
The solutions are:
Any X from R.

> 8 - 6x + 5.6x^3 = 3 ?
Reduced form: 5.6x^3-6x+5 = 0
Polynomial degree: 3
The polynomial degree is strictly greater than 2, I can't solve.

> 5 + 4x - 9.3x^2 = 1 ?
Reduced form: -9.3x^2+4x+4 = 0
Polynomial degree: 2
Discriminant: Strictly positive (164.8)
The solutions are:
0.905239
-0.475131

> 5 + 4x = 4 ?
Reduced form: 4x+1 = 0
Polynomial degree: 1
The solution is:
-0.25

> 1 = 1 ?
Reduced form: 0 = 0
Polynomial degree: 0
The equality is: True

> 8 - 6x + x^3 = x^3 ?
Reduced form: 0x^3-6x+8 = 0
Polynomial degree: 1
The solution is:
-4_-3

> 0x^2+1=0 ?
Reduced form: 0x^2+1 = 0
Polynomial degree: 0
No solution.

> 4 + 5 = ?
9

> 4 + = 5 ?
Compiler::Parser::InvalidSyntax: Unexpected 'EQUAL', expected 'PAREN_L | IDENTIFIER | BRACK_L | NUMBER'.

> 4 5 = -1 ?
Compiler::Parser::InvalidSyntax: Unexpected 'NUMBER(5)', expected 'EQUAL'.

> 4 +
Compiler::Parser::InvalidSyntax: Unexpected 'END', expected 'PAREN_L | IDENTIFIER | BRACK_L | NUMBER'.

> f(x) = x + 5.4
f(x) = (5.4 + x)

> a = 2 * 3.1415 * 5
a = 31.415

> 4.5 + f(5) = ?
14.9

> 4.5 + A = ?
35.915

> M = [[1,2,3];[4,5,6]] + [[6,5,4];[3,2,1]]
M = [[7, 7, 7], [7, 7, 7]]

> C = 5 + i
C = 5+i

> 2 * x^2 + 3 * x - 1 = 0 ?
Reduced form: 2x^2+3x-1 = 0
Polynomial degree: 2
Discriminant: Strictly positive (17.0)
The solutions are:
-1.78078
0.280776

> (2 + a) / 3a = ?
0.354555

> f(f(x))=?
(10.8 + x)

> f(x) + 2*x^2 = x^2 ?
Reduced form: x^2+x+5.4 = 0
Polynomial degree: 2
Discriminant: Strictly negative (-20.6)
The solutions are:
-0.5-2.26936i
-0.5+2.26936i

> 2x^2 + 3x = -x^2 - 3 ?
Reduced form: 3x^2+3x+3 = 0
Polynomial degree: 2
Discriminant: Strictly negative (-27.0)
The solutions are:
-0.5-0.866025i
-0.5+0.866025i

> 3*(x)^2 + 3x^(1+1) = -(x)^2 - 3 ?
Reduced form: 7x^2+3 = 0
Polynomial degree: 2
Discriminant: Strictly negative (-84.0)
The solutions are:
-0.654654i
0.654654i

> (3 + 4) * (3 + i * 3 - 1) / 3 = ?
14_3+7i

> (4 - i) * (4 / 2 + 1)i = ?
3+12i

> f(5+3) - f(5+3) = ?
0

> (-x^2*5+4x-3-x) + (2x+4) - x^2*(4-3) + (x-3-2*(4+x+3)*4) - x = 0?
Reduced form: -6x^2-3x-58 = 0
Polynomial degree: 2
Discriminant: Strictly negative (-1383.0)
The solutions are:
-0.25+3.09906i
-0.25-3.09906i

> ((-x^2*5+4x-3-x) + (2x+4) - x^2*(4-3) + (x-3-2*(4+x+3)*4) - x) / 2x = ?
(((-58 + (-3 * x)) + (-6 * (x ^ 2))) / (2 * x))

> (x*y*z) * (x+2) = ?
((((2 * x) + (x ^ 2)) * y) * z)

> x + (-2 - (y)) = ?
((-2 + x) - y)

> y * (x - (-5 ^ (y))) = ?
(((5 ^ y) + x) * y)

> 5 / (i / (y - (-2 % (y)))) = ?
((5i * (-2 % y)) + (-5i * y))

> y * (5 + (i * (x + (y)))) = ?
(((5 + (i * x)) * y) + (i * (y ^ 2)))

> -2 % (y * (5 - (i * (x - (y))))) = ?
(-2 % (((5 - (i * x)) * y) + (i * (y ^ 2))))

> -3+x*(42x+4-x)+5x+1-x*(-2-6/(8%3))=?
((-2 + (14 * x)) + (41 * (x ^ 2)))
```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
