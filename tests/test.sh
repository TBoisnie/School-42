#!/bin/zsh

function compile_and_run ()
{
    clang++ -Werror -Wextra -Wall -std=c++20 ex$1.cpp
    ./a.out
    rm a.out
}

for i in {00..14}
do
    compile_and_run $i
done
