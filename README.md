# 42 - Exam - MiniServ

Implementation in `C` of a mini chat server (multiple clients, receive/send messages).

> [!NOTE]
> Exams are done in a clean and disconnected environment.
>
> What we have :
> * Access to a terminal
> * Access to man-pages (through the terminal)
>
> What we do __NOT__ have :
> * Access to anything else (no internet, no code samples, no notes, ...)

## Requirements

- [GCC](https://gcc.gnu.org/)

## Getting Started

1. Compile

	```sh
	# Build
	gcc -Werror -Wextra -Wall -o miniserv ./srcs/main.c
	```

1. Test

	```sh
	# Run
	./miniserv 8080

	# Connect
	nc 127.0.0.1 8080
	```

## Example

	```sh
	# Terminal 1
	./miniserv 8080

	# Terminal 2
	nc 127.0.0.1 8080
	server: client 4 just arrived
	client 4: Hello World!
	server: client 4 just left

	# Terminal 3
	nc 127.0.0.1 8080
	Hello World!
	^C
	```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
