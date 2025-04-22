#!/bin/sh

SIZE=3                # puzzle size (min=3)
ITERATION=10000       # tile moves to generate puzzle
N=50                  # number of puzzle
HEURISTIC="manhattan" # manhattan, euclidean, hamming, conflict, uniform_cost
GREEDY=""             # -g, ""

echo "Cleaning previously generated tests."
rm -r solvables 2&> /dev/null
rm -r unsolvables 2&> /dev/null

mkdir solvables
mkdir unsolvables

for i in `seq 1 $N`
do
    SOLVABLE_PATH="./solvables/${i}.txt"
    UNSOLVABLE_PATH="./unsolvables/${i}.txt"

    echo "Generating puzzles ${i}: ${SIZE} x ${SIZE}, with ${ITERATION} iterations."

    python3 generator.py --solvable -i $ITERATION $SIZE > $SOLVABLE_PATH
    python3 generator.py --no-solvable -i $ITERATION $SIZE > $UNSOLVABLE_PATH

    SOLVABLE_PATH="../tests/${SOLVABLE_PATH}"
    UNSOLVABLE_PATH="../tests/${UNSOLVABLE_PATH}"

    echo "# --------------------" >> $SOLVABLE_PATH
    echo "# --------------------" >> $UNSOLVABLE_PATH

    echo "Solving puzzles ${i}."
    python3 ../srcs/main.py $GREEDY -htc $HEURISTIC $SOLVABLE_PATH >> $SOLVABLE_PATH
    python3 ../srcs/main.py $GREEDY -htc $HEURISTIC $UNSOLVABLE_PATH >> $UNSOLVABLE_PATH
done

echo "Generation complete."
