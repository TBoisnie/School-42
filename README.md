# 42 - AI - N Puzzle

Implementation in `python` of the _A*_ algorithm with 4 heuristics (_manhattan_, _euclidean_, _hamming_, _linear conflict_) to solve a N-Puzzle.

## Requirements

- [Python 3](https://www.python.org/)

## Getting Started

1. Generate a puzzle

	```sh
	python3 ./tests/generator.py [ --solvable | --no-solvable ] [ --iterations N ] SIZE > puzzle.txt
		# --solvable, --no-solvable : Define if generated puzzle should solvable or not (default: random)
		# --iterations : Number of moved tiles to shuffle the puzzle
		# SIZE : Puzzle size (must be >= 3)
	```

1. Solve

	```sh
	python3 ./srcs/main.py [ -n SIZE [ -i ITERATIONS ] ] [ -g ] [ -htc HEURISTIC ] [ FILE ]
		# -n : Puzzle size generated (must be >= 3, default: 3) (if no file provided)
		# -i : Number of moved tiles to shuffle the puzzle (default: 20)
		# -g : Define if A* algorithm should be greedy or not
		# -htc : Define which heuristic to use (choices : manhattan, euclidean, hamming, conflict, uniform_cost ; default : manhattan)
		# FILE : File containing the puzzle to solve (if not defined, a random one is generated)
	```

1. Test

	```sh
	# Change directory
	cd ./tests

	# Configure tester
	vim ./test.sh

	# Generate and solve multiple puzzles
	./test.sh

	# Check
	cat ./solvables/*.txt
	cat ./unsolvables/*.txt
	```

## Example

```sh
# Generate puzzle
python3 ./tests/generator.py --solvable 3 > puzzle.txt

# Show Generated puzzle
cat puzzle.txt
# This puzzle is solvable
3
1 2 4
6 0 7
8 3 5

# Solve
python3 ./srcs/main.py puzzle.txt

Source Puzzle:
1 2 4
6 0 7
8 3 5
Destination Puzzle:
1 2 3
8 0 4
7 6 5

Solution found (16 moves).
Step 0:
1 2 4
6 0 7
8 3 5

Step 1:
1 2 4
6 3 7
8 0 5

Step 2:
1 2 4
6 3 7
0 8 5

Step 3:
1 2 4
0 3 7
6 8 5

Step 4:
0 2 4
1 3 7
6 8 5

Step 5:
2 0 4
1 3 7
6 8 5

Step 6:
2 3 4
1 0 7
6 8 5

Step 7:
2 3 4
1 7 0
6 8 5

Step 8:
2 3 0
1 7 4
6 8 5

Step 9:
2 0 3
1 7 4
6 8 5

Step 10:
0 2 3
1 7 4
6 8 5

Step 11:
1 2 3
0 7 4
6 8 5

Step 12:
1 2 3
7 0 4
6 8 5

Step 13:
1 2 3
7 8 4
6 0 5

Step 14:
1 2 3
7 8 4
0 6 5

Step 15:
1 2 3
0 8 4
7 6 5

Step 16:
1 2 3
8 0 4
7 6 5

Heuristic: manhattan
Greedy: False
Complexity Time:  152
Complexity Space: 124
```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
