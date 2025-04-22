#!/usr/bin/env bash

LOGS_DIR="logs"
EXE_DIR="../bins"

LS_LOG="$LOGS_DIR/ls.log"
FT_LOG="$LOGS_DIR/ft.log"
DIFF_LOG="$LOGS_DIR/diff.log"

FLAGS_POOL="acgGilnoprRsStuU"
FILES_POOL=("/tmp" "../srcs" "test.sh" "../Makefile" "../srcs/main.c" "/bin")

FLAGS=""
FILES=""

if [[ ! -f "$EXE_DIR/ft_ls" ]]
then
	cd ..
	make re
	cd - > /dev/null
fi

if [[ -z "$1" ]]
then
	FLAGS=$(echo $FLAGS_POOL | fold -w1 | shuf | tr -d '\n')
	FLAGS="-${FLAGS:0:(($RANDOM % ${#FLAGS} + 1))}"

	echo "Flags: $FLAGS"

	FILES=( $(shuf -e "${FILES_POOL[@]}") )
	FILES=( "${FILES[@]:0:(($RANDOM % ${#FILES[@]} + 1))}" )

	echo "Files: ${FILES[@]}"
fi

mkdir -p $LOGS_DIR

$EXE_DIR/ft_ls                  $FLAGS $FILES $* > $FT_LOG 2>&1
LC_ALL=C    ls --color=never -1 $FLAGS $FILES $* > $LS_LOG 2>&1

diff --text $LS_LOG $FT_LOG > $DIFF_LOG && echo "Fine"
