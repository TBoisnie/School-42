# 42 - Core - CPP

Multiple short exercices to learn `Object Oriented Programming` concepts in `C++` (`inheritance`, `polymorphism`, `class`, `object`, ...).
- Day 0 : Array, `std::cin`, `std::cout`
- Day 1 : Pointer, Reference, `new`, `delete`, `std::stream`
- Day 2 : Implementation of a "fixed point" decimal class
- Day 3 : Inheritance, Overloading
- Day 4 : Interface, `abstract`, Factory, Prototype
- Day 5 : Exception, Polymorphism, Builder
- Day 6 : Casting, Serialization
- Day 7 : Template (Generics), Iterator
- Day 8 : Standard algorithms and data structures

## Requirements

- [Clang](https://clang.llvm.org/)

## Getting Started

1. Compile

	```sh
	# Change directory
	cd ./day_*
	cd ./srcs/ex0*

	# Make (if Makefile exists)
	make [ all | clean | fclean | re ]
		# all : Compile required files and build executable
		# clean : Delete object ".o" files
		# fclean : Delete object ".o" and executable files
		# re : Run "fclean" then "all"

	# Build (if Makefile does not exist)
	clang++ -Werror -Wextra -Wall --std=c++98 *.cpp
	```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
