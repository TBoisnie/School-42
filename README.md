# 42 - Core - Minishell

Implementation of a mini `Shell`, with support for few built-in (`cd`, `echo`, `pwd`, `env`, `export`, `unset`, `exit`), pipes (`|`), input/output redirections (`>`, `>>` and `<`), strings, variables...

## Requirements

- [Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)

## Getting Started

1. Compile

	```sh
	# Change directory
	cd ./srcs

	# Make
	make [ all | clean | fclean | re | bonus ]
		# all : Compile required files and build executable
		# clean : Delete object ".o" files
		# fclean : Delete object ".o" and executable files
		# Re : Run "fclean" then "all"
		# bonus : Same as "all"
	```

1. Execute

	```sh
	# Run
	./minishell
	```

## Examples

```sh
❯ ./minishell

~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
~  (\___/)                          ~
~  (=^.^=)      MiniShell  (v1.0)   ~
~  (")_(")                          ~
~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~
/home/tboisnie/42-MiniShell/srcs
λ ls
builtin  environnement  get_input  Makefile   minishell.c  minishell.o  separator
command  execute        libft      minishell  minishell.h  parser       signal
/home/tboisnie/42-MiniShell/srcs
λ export TEST="test"
/home/tboisnie/42-MiniShell/srcs
λ echo $TEST
test
/home/tboisnie/42-MiniShell/srcs
λ ls -laRth > /tmp/ls.log ; head -n 5 /tmp/ls.log
.:
total 112K
-rw-r--r--  1 tboisnie tboisnie 2.0K Apr 19 19:12 Makefile
-rwxr-xr-x  1 tboisnie tboisnie  47K Apr 19 19:06 minishell
drwxr-xr-x 11 tboisnie tboisnie 4.0K Apr 19 19:06 .
/home/tboisnie/42-MiniShell/srcs
λ tail -n 5 < /tmp/ls.log
-rw-r--r-- 1 tboisnie tboisnie 1.1K Apr 19 19:05 length.c
-rw-r--r-- 1 tboisnie tboisnie 1.3K Apr 19 19:05 copy.c
-rw-r--r-- 1 tboisnie tboisnie 1.1K Apr 19 19:05 clear.c
-rw-r--r-- 1 tboisnie tboisnie 1.2K Apr 19 19:05 append.c
drwxr-xr-x 3 tboisnie tboisnie 4.0K Apr 19 19:05 ..
/home/tboisnie/42-MiniShell/srcs
λ ls -l | wc -l
15
/home/tboisnie/42-MiniShell/srcs
λ ls -l | wc -l >> /tmp/ls.log ; tail -n 1 /tmp/ls.log
15
/home/tboisnie/42-MiniShell/srcs
λ exit
```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
