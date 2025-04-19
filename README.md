# 42 - Core - LibASM

Reimplementation of few `C` functions in `Assembler`, then compile them into a tiny static library.

## Requirements

- [Nasm](https://www.nasm.us/)
- [Make](https://www.gnu.org/software/make/)
- [AR](https://www.gnu.org/software/coreutils/)

## Getting Started

1. Compile

	```sh
	# Change directory
	cd ./srcs

	# Make
	make [ all | clean | fclean | re ]
		# all : Compile required files and build library
		# clean : Delete object ".o" files
		# fclean : Delete object ".o" and library ".a" files
		# re : Run "fclean" then "all"
	```

1. Test

	```sh
	# Compile
	make test

	# Run
	./test
	```

1. Use the library : __libasm.a__

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
