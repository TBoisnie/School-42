# 42 - Unix - Malloc

Reimplementation in `C` of the `malloc`, `realloc` and `free` functions using `mmap`, `munmap` and compiling them into a tiny dynamic library.

## Requirements

- [Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)

## Getting Started

1. Compile

	```sh
	# Make
	make [ all | clean | fclean | re ]
		# all : Compile required files and build library ".so"
		# clean : Delete object ".o" files
		# fclean : Delete object ".o" and library ".so" files
		# Re : Run "fclean" then "all"
	```

1. Test

	```sh
	# Change directory
	cd ./tests

	# Run
	./run_all.sh
	```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
