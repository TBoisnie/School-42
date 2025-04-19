# 42 - Core - Philosophers

Introduction to concurrency programming through 3 variations of the well known dining philosophers problem.
- Version 1 : `thread` + `mutex`
- Version 2 : `thread` + `semaphore`
- Version 3 : `fork` + `thread` + `semaphore`

## Requirements

- [Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)

## Getting Started

1. Compile

	```sh
	# Change directory
	cd ./srcs/philo_*
		# one : thread + mutex
		# two : thread + semaphore
		# three : fork (process) + thread + semaphore

	# Make
	make [ all | clean | fclean | re ]
		# all : Compile required files and build executable
		# clean : Delete object ".o" files
		# fclean : Delete object ".o" and executable files
		# re : Run "fclean" then "all"
	```

1. Execute

	```sh
	# Run
	./philo_* 4 800 200 150 21
		# number_of_philosophers : 4
		# time_to_die (ms) : 800
		# time_to_eat (ms) : 200
		# time_to_sleep (ms) : 150
		# number_of_times_each_philosopher_must_eat : 21
	```

## Examples

```sh
❯ ./philo_one 4 800 200 150 3
1       1 is thinking
1       1 has taken a fork
1       1 has taken a fork
1       1 is eating
12      3 is thinking
12      3 has taken a fork
12      3 has taken a fork
12      3 is eating
17      2 is thinking
20      4 is thinking
207     2 has taken a fork
208     4 has taken a fork
213     3 is sleeping
213     4 has taken a fork
213     4 is eating
214     2 has taken a fork
214     2 is eating
214     1 is sleeping
364     1 is thinking
373     3 is thinking
418     1 has taken a fork
429     1 has taken a fork
429     1 is eating
430     2 is sleeping
431     3 has taken a fork
432     3 has taken a fork
435     4 is sleeping
446     3 is eating
586     4 is thinking
590     2 is thinking
629     1 is sleeping
629     2 has taken a fork
630     4 has taken a fork
648     4 has taken a fork
648     4 is eating
650     2 has taken a fork
651     2 is eating
654     3 is sleeping
782     1 is thinking
805     3 is thinking
850     4 is sleeping
850     1 has taken a fork
851     2 is sleeping
851     1 has taken a fork
851     1 is eating
857     3 has taken a fork
857     3 has taken a fork
857     3 is eating
1000    4 is thinking
1002    2 is thinking
1060    3 is sleeping
1060    1 is sleeping
1061    4 has taken a fork
1061    4 has taken a fork
1061    4 is eating
1061    2 has taken a fork
1061    2 has taken a fork
1061    2 is eating
1261    4 is sleeping
1264    2 is sleeping
```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
