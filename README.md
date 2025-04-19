# 42 - Core - Get Next Line

Implementation of a `get_next_line` function in C, to read content, line by line (split on `\n`), from one or multiple file descriptor at the same time.

## Requirements

- [GCC](https://gcc.gnu.org/)

## Getting Started

1. Compile

	```sh
	# Change directory
	cd ./tests

	# One FD at a time (Required)
	gcc -Werror -Wextra -Wall -D BUFFER_SIZE=42 ../srcs/get_next_line.c ../srcs/get_next_line_utils.c main.c

	# Multiple FD at the same time (Bonus, but uses the same code as required part, only files name are differents)
	gcc -Werror -Wextra -Wall -D BUFFER_SIZE=42 ../srcs/get_next_line_bonus.c ../srcs/get_next_line_utils_bonus.c main.c
	```

1. Test

	```
	# Run
	./a.out
	```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
