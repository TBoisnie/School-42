#!/bin/python3

from math import sqrt
import argparse
import re

from AStar     import AStar, PathNotFound
from Heuristic import Heuristic
from Metrics   import Metrics
from Puzzle    import Puzzle
from Utils     import Utils

# Heuristics: At least 3 (Manhattan required)
# Cost: 1
# Print
# - Total number of states ever selected in the "opened" set (complexity in time)
# - Maximum number of states ever represented in memory at the same time during the search (complexity in size)
# - Number of moves required to transition from the initial state to the final state, according to the search
# - The ordered sequence of states that make up the solution, according to the search
# - The puzzle may be unsolvable, in which case you have to inform the user and exit

class FileInvalidContent(Exception):
    pass

def parse_file(filepath_):
    size = None
    grid = []

    with open(filepath_) as f:
        for i, line in enumerate(f, start=1):
            # Size
            if size == None:
                find = re.match(r'^\s*(\d+)\s*(#.*)*$', line)
                if (find):
                    size = int(find.groups()[0])
                    if size < 3:
                        raise FileInvalidContent(f"[Error] Parsing ({i}): Invalid size ({size} < 3).")
                    continue
            # Grid
            elif size != None and len(grid) < size:
                find = re.match(r'^\s*' + r'((\d+)(\s+))' * size + r'\s*(#.*)?$', line)
                if (find):
                    grid.append(list(map(int, find.groups()[1::3])))
                    continue
                raise FileInvalidContent(f"[Error] Parsing ({i}): Invalid puzzle row.")
            # Comments
            find = re.match(r'^\s*(#.*)*$', line)
            if not (find):
                raise FileInvalidContent(f"[Error] Parsing ({i}): Invalid comment row.")

    # Incomplete file
    if size == None or len(grid) != size:
        raise FileInvalidContent(f"[Error] Parsing : Invalid size ({size}) or grid ({len(grid)} rows).")

    grid = Utils.matrix_to_list(grid)

    # Invalid grid values
    if sorted(grid) != [*range(size * size)]:
        raise FileInvalidContent("[Error] Parsing : Invalid grid numbers (duplicated/missing).")

    return grid


if __name__ == "__main__":

    heuristics = {}
    heuristics["manhattan"]    = Heuristic.manhattan
    heuristics["euclidean"]    = Heuristic.euclidean
    heuristics["hamming"]      = Heuristic.hamming
    heuristics["conflict"]     = Heuristic.linear_conflict
    heuristics["uniform_cost"] = Heuristic.uniform_cost

    #
    # Args
    #
    parser = argparse.ArgumentParser(
        prog="n_puzzle",
        description="N-Puzzle solver using A* algorithm and multiple heuristics available.",
        allow_abbrev=False
    )

    parser.add_argument('-n',   action='store',            default=3,           type=int,  help='Define puzzle sqrt(size) (must be >= 3, default = 3).')
    parser.add_argument('-i',   action='store',            default=20,          type=int,  help='Define number of iteration to generate random puzzle (must be >= 0, default = 20).')
    parser.add_argument('-g',   action="store_true",                                       help='Define if A* should be Greedy (default = false).')
    parser.add_argument('-htc', choices=heuristics.keys(), default='manhattan', type=str,  help='Change heuristic (default = manhattan).')
    parser.add_argument('file', action='store', nargs='?',                      type=str,  help='File containing the Puzzle to solve (override -n and -i).')

    args = parser.parse_args()

    #
    # Config
    #
    config = {}
    config["heuristic"] = heuristics[args.htc]
    config["n"]         = args.n    if args.n >= 3 else 3
    config["iteration"] = args.i    if args.i >= 0 else 20
    config["file"]      = args.file if args.file   else None
    config["greedy"]    = args.g    if not args.htc == "uniform_cost" else False

    if args.g and args.htc == "uniform_cost":
        print("[Warning] Can not be Greedy and use Uniform Cost at the same time (Ignoring Greedy flag).")

    #
    # Import
    #
    try:
        grid = parse_file(config["file"]) if config["file"] else [ *range(0, config["n"] * config["n"]) ]
    except FileNotFoundError:
        print("[Error] Input file: Not found.")
        exit()
    except FileInvalidContent as e:
        print(e)
        exit()

    #
    # Parse
    #
    n = int(sqrt(len(grid)))

    dst = Puzzle(n, [ *range(0, n * n) ])
    dst.orderize()

    src = Puzzle(n, grid)
    if not config["file"]:
        src.orderize()
        src.randomize(config["iteration"])

    #
    # Solve
    #
    print(f"Source Puzzle:")
    Utils.print_matrix(Utils.list_to_matrix(src.tiles, n))
    print(f"Destination Puzzle:")
    Utils.print_matrix(Utils.list_to_matrix(dst.tiles, n))
    print()

    # Solvability
    if not src.is_solvable(dst):
        print("Puzzle is not solvable.")
        exit()

    # Run
    metrics = Metrics()

    try:
        AStar.run(src, dst, config["heuristic"], metrics, config["greedy"])
    except PathNotFound:
        print("No solution found.")
    else:
        print(f"Solution found ({len(metrics.path) - 1} moves).")

    #
    # Print
    #
    for i, node in enumerate(metrics.path):
        print(f"Step {i}:")
        Utils.print_matrix(Utils.list_to_matrix(node.value.tiles, n))
        print()

    print(f"Heuristic: {args.htc}")
    print(f"Greedy: {config['greedy']}")
    print(f"Complexity Time:  {metrics.time_complexity}")
    print(f"Complexity Space: {metrics.space_complexity}")
    print()
