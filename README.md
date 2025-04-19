# 42 - Core - LibFT

Re/Implementation of some `C` functions, data structures, and compile them into a tiny static library.

## Requirements

- [Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)
- [AR](https://www.gnu.org/software/coreutils/)

## Getting Started

1. Compile

	```sh
	# Change directory
	cd ./srcs

	# Make
	make [ all | clean | fclean | re | bonus ]
		# all : Compile required files and build library
		# clean : Delete object ".o" files
		# fclean : Delete object ".o" and library ".a" files
		# Re : Run "fclean" then "all"
		# bonus : Same as "all" but with bonuses (linked list)
	```

1. Use the library : __libft.a__

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
