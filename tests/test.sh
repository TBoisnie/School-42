#!/usr/bin/env bash

# ==============================================================================
# Variables
# ==============================================================================
TEST_START=0
TEST_END=10
LOGS_DIR="../logs"

# ==============================================================================
# Functions
# ==============================================================================
function compile_and_run ()
{
    echo "(ex$1) Compiling..."
    clang++ -Werror -Wextra -Wall -std=c++20 \
        ../srcs/Set.cpp \
        ../srcs/Bool.cpp \
        ../srcs/ReadySetBoole.cpp \
        ../srcs/ReversePolishNotation/Node.cpp \
        ../srcs/ReversePolishNotation/Utils.cpp \
        ex$1.cpp

    echo "(ex$1) Running..."
    ./a.out > "$LOGS_DIR/ex$1.log" 2>&1

    echo "(ex$1) Cleaning..."
    rm a.out
}

# ==============================================================================
# Main
# ==============================================================================
echo "Clearing previous logs."

if [ -d "$LOGS_DIR" ]
then
    rm -r $LOGS_DIR;
fi

mkdir $LOGS_DIR

for i in $(seq -f %02g $TEST_START $TEST_END)
do
    compile_and_run $i
done

echo "Done. (see $LOGS_DIR for tests outputs)"
