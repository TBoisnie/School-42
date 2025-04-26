#!/bin/bash

# Constants
OUTPUT_DIR=".logs"
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
ITERATION="$2"

if [[ ! " ${CONTAINERS[*]} " =~ [[:space:]]${CONTAINER}[[:space:]] ]]
then
	echo "Invalid container: $CONTAINER"
	echo "Accepted: ${CONTAINERS[@]}"
	exit
fi

if [[ -z $ITERATION ]]
then
	ITERATION=5
fi

if [[ ! ( $ITERATION =~ ^[0-9]+$ ) || $ITERATION -lt 0 || $ITERATION -gt 1000 ]]
then
	echo "Invalid iteration: $ITERATION"
	echo "Accepted (default = 5): 1-100000"
	exit
fi

OUTPUT_FILE="$OUTPUT_DIR/bulk_$CONTAINER.log"
mkdir -p $OUTPUT_DIR
> $OUTPUT_FILE

for _ in $( seq $ITERATION )
do
	echo -ne "\rRun $_"
	./test.sh $CONTAINER all classic >> $OUTPUT_FILE
done

echo ""
