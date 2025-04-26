#!/bin/bash

# Constants
OUTPUT_DIR=".logs"
HEADER_DIR="../../srcs"
SOURCE_DIR="./container"
CONTAINERS=(
	list
	forward_list
	set
	map
	multiset
	multimap
	unordered_set
	unordered_map
	unordered_multiset
	unordered_multimap
	stack
	queue
	priority_queue
	fibonacci_heap
	deque
	vector
)

# Arguments
CONTAINER="$1"
NAMESPACE="$2"
MODE="$3"
SEED="$4"

if [[ ! " ${CONTAINERS[*]} " =~ [[:space:]]${CONTAINER}[[:space:]] ]]
then
	echo "Invalid container: $CONTAINER"
	echo "Accepted: ${CONTAINERS[@]}"
	exit
fi

if [[ -z $NAMESPACE ]]
then
	NAMESPACE="all"
fi

if [[ $NAMESPACE != "ft" && $NAMESPACE != "std" && $NAMESPACE != "all" ]]
then
	echo "Invalid namespace: $NAMESPACE"
	echo "Accepted (default = all): ft std all"
	exit
fi

if [[ -z $MODE ]]
then
	MODE="classic"
fi

if [[ $MODE != "perf" && $MODE != "classic" ]]
then
	echo "Invalid mode: $MODE"
	echo "Accepted (default = classic): perf classic"
	exit
fi

if [[ -z $SEED ]]
then
	SEED=$RANDOM
	echo -e "\nGenerated seed: $SEED"
fi

if [[ ! ( $SEED =~ ^[0-9]+$ ) || $SEED -lt 0 || $SEED -gt 100000 ]]
then
	echo "Invalid seed: $SEED"
	echo "Accepted (default = \$RANDOM): 1-100000"
	exit
fi

# Setup
if [[ ! -d $OUTPUT_DIR ]]
then
	mkdir $OUTPUT_DIR
fi

# Define
[[ $MODE == "perf" ]] && PERF="-DPERFORMANCE_MODE" || PERF=""

# Compilation
if [[ $NAMESPACE == "all" ]]
then
	ft_exe="$OUTPUT_DIR/ft_$CONTAINER"

	g++ -Werror -Wextra -Wall -std=c++98 -I $HEADER_DIR $SOURCE_DIR/$CONTAINER.cpp -DNS=ft -DSEED=$SEED $PERF -o $ft_exe \
		&& ./$ft_exe > $ft_exe.log \
		&& rm $ft_exe

	std_exe="$OUTPUT_DIR/std_$CONTAINER"

	g++ -Werror -Wextra -Wall $SOURCE_DIR/$CONTAINER.cpp -DSEED=$SEED $PERF -o $std_exe \
		&& ./$std_exe > $std_exe.log \
		&& rm $std_exe

	diff="$OUTPUT_DIR/diff_$CONTAINER.log"

	diff $ft_exe.log $std_exe.log > $diff

	echo -e "----------------------------------------"
	echo -e "Difference ft_$CONTAINER <-> std_$CONTAINER"
	echo -e "----------------------------------------"
	cat $diff

elif [[ $NAMESPACE == "ft" ]]
then
	exe="$OUTPUT_DIR/ft_$CONTAINER"

	g++ -Werror -Wextra -Wall -g -std=c++98 -I $HEADER_DIR $SOURCE_DIR/$CONTAINER.cpp -DNS=ft -DSEED=$SEED $PERF -o $exe \
		&& valgrind -s --track-origins=yes --leak-check=full ./$exe \
		&& rm $exe

	# g++ -Werror -Wextra -Wall -g -pg -std=c++98 -I $HEADER_DIR $SOURCE_DIR/$CONTAINER.cpp -DNS=ft -DSEED=$SEED $PERF -o $exe \
	# 	&& ./$exe \
	# 	&& gprof $exe gmon.out > profiling.txt \
	# 	&& mv gmon.out profiling.txt $OUTPUT_DIR
	# 	&& rm $exe

else # $NAMESPACE = std
	exe="$OUTPUT_DIR/std_$CONTAINER"

	g++ -Werror -Wextra -Wall -g $SOURCE_DIR/$CONTAINER.cpp -DSEED=$SEED $PERF -o $exe \
		&& valgrind --track-origins=yes --leak-check=full ./$exe \
		&& rm $exe

fi
