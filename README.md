# 42 - Misc - Abstract Data

Reimplementation in `C++` of multiple containers with their iterators.

Containers :
- Deque
- Fibonacci Heap
- Forward List
- Hash Table
- List
- Map
- Multi Map
- Multi Set
- Priority Queue
- Queue
- Red Black Tree
- Set
- Stack
- Unordered Map
- Unordered Multi Map
- Unordered Multi Set
- Unordered Set
- Vector

## Requirements

- [Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)

## Getting Started

1. Test (static)

	```sh
	# Change directory
	cd ./tests/static

	# Run
	make
	```

1. Test (monkey)

	```sh
	# Change directory
	cd ./tests/monkey

	# Run
	./monkey.sh <container> [<seed>] [<iterations>]
		# container :
		# - list, vector, deque, map, set, multimap, multiset, stack, priority_queue
		# seed :
		#   integer
		# iterations :
		#   integer
	```

1. Test (custom)

	```sh
	# Change directory
	> cd ./tests/custom

	# Run (one)
	> ./test.sh <container> [<namespace>] [<mode>] [<seed>]
		# container :
		#   list, forward_list, set, map, multiset, multimap, unordered_set, unordered_map, unordered_multiset, unordered_multimap, stack, queue, priority_queue, fibonacci_heap, deque, vector
		# namespace (default : all) :
		#   std, ft, all
		# mode (default : classic) :
		#   classic, perf
		# seed (default : random) :
		#   integer

	# Run (bulk)
	./bulk.sh <container> [<iteration>]
		# container :
		#   see above
		# iteration (default : 5) :
		#   1-100000
	```

## Examples

```sh
> ./bulk.sh list 5
Run 5

> cat ./logs/bulk_list.log

Generated seed: 26364
----------------------------------------
Difference ft_list <-> std_list
----------------------------------------

Generated seed: 26068
----------------------------------------
Difference ft_list <-> std_list
----------------------------------------

Generated seed: 16719
----------------------------------------
Difference ft_list <-> std_list
----------------------------------------

Generated seed: 3241
----------------------------------------
Difference ft_list <-> std_list
----------------------------------------

Generated seed: 22797
----------------------------------------
Difference ft_list <-> std_list
----------------------------------------

> ./test.sh list all perf

Generated seed: 15299
 ----------------------------------------
 Difference ft_list <-> std_list
 ----------------------------------------
1,8c1,8
< Time Insert (us): 191686
< Time Erase (us): 20523
< Time Assign (us): 49282
< Time Sort (us): 1112383
< Time Unique (us): 140273
< Time Merge (us): 496637
< Time Remove If (us): 266956
< Time Total (us): 4278764
---
> Time Insert (us): 182856
> Time Erase (us): 16388
> Time Assign (us): 49194
> Time Sort (us): 1523893
> Time Unique (us): 143121
> Time Merge (us): 331484
> Time Remove If (us): 346873
> Time Total (us): 5087167
```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
