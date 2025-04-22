# 42 - Unix - FT Ls

Reimplementation in `C` of the `ls` command with some flags support (but not locale: LC_ALL=C).

## Requirements

- [Make](https://www.gnu.org/software/make/)
- [GCC](https://gcc.gnu.org/)

## Getting Started

1. Compile

	```sh
	# Make
	make [ all | clean | fclean | re ]
		# all : Compile required files and build executable
		# clean : Delete object ".o" files
		# fclean : Delete object ".o" and executable files
		# Re : Run "fclean" then "all"
	```

1. Execute

	```sh
	# Run
	./bins/ft_ping -h
	```

## Examples

```sh
> ./bins/ft_ls --help

List information about the files (current directory by default)

Usage: ft_ls [options...] [file...]

Options:
    -a, --all               Do not ignore entries starting with '.'.
    -c                      With '-lt': sort by, and show, ctime. With '-l': show ctime and sort by name. Otherwise: sort by ctime, newest first.
    --color                 Enable colored output.
    -g                      Like '-l', but hide owner user.
    -G, --no-group          With '-l', do not print group names.
    --help                  Display this help and exit.
    -i, --inode             Print the index number of each file.
    -l                      Use a long listing format.
    -n, --numeric-uid-gid   Like '-l', but list numeric user and group IDs.
    -o                      Like '-l', but do not list group information.
    -p                      Append '/' indicator to directories.
    -r, --reverse           Reverse order while sorting.
    -R, --recursive         List subdirectories recursively.
    -s, --size              Print the allocated size of each file, in blocks.
    -S                      Sort by file size, largest first.
    -t                      Sort by time, newest first.
    -u                      With '-lt': sort by, and show, access time. With '-l': show access time and sort by name. Otherwise: sort by access time, newest first.
    -U                      Do not sort. List entries in directory order.
    --zero                  End each output line with NUL ('\0'), instead of newline ('\n').
    -1                      List one file per line (always active).

> ./bins/ft_ls -l

total 32
-rw-r--r-- 1 tboisnie tboisnie 3922 Apr 22 23:01 Makefile
-rw-r--r-- 1 tboisnie tboisnie 2243 Apr 23 00:03 README.md
drwxr-xr-x 3 tboisnie tboisnie 4096 Apr 23 00:02 bins
drwxr-xr-x 2 tboisnie tboisnie 4096 Apr 22 23:01 docs
drwxr-xr-x 2 tboisnie tboisnie 4096 Apr 22 23:01 incs
drwxr-xr-x 3 tboisnie tboisnie 4096 Apr 22 23:01 libs
drwxr-xr-x 7 tboisnie tboisnie 4096 Apr 22 23:01 srcs
drwxr-xr-x 2 tboisnie tboisnie 4096 Apr 22 23:01 tests

> ./bins/ft_ls -lipsSR ./srcs

./srcs:
total 24
1236225 4 drwxr-xr-x 2 tboisnie tboisnie 4096 Apr 22 23:01 error/
1236227 4 drwxr-xr-x 2 tboisnie tboisnie 4096 Apr 22 23:01 file/
1236231 4 drwxr-xr-x 2 tboisnie tboisnie 4096 Apr 22 23:01 parser/
1236233 4 drwxr-xr-x 2 tboisnie tboisnie 4096 Apr 22 23:01 render/
1236237 4 drwxr-xr-x 2 tboisnie tboisnie 4096 Apr 22 23:01 sort/
1236230 4 -rw-r--r-- 1 tboisnie tboisnie 2426 Apr 22 23:01 main.c

./srcs/error:
total 4
1236226 4 -rw-r--r-- 1 tboisnie tboisnie 439 Apr 22 23:01 show_error.c

./srcs/file:
total 8
1236228 4 -rw-r--r-- 1 tboisnie tboisnie 1155 Apr 22 23:01 file_init.c
1236229 4 -rw-r--r-- 1 tboisnie tboisnie  446 Apr 22 23:01 file_new.c

./srcs/parser:
total 8
1236232 8 -rw-r--r-- 1 tboisnie tboisnie 4469 Apr 22 23:20 parse_args.c

./srcs/render:
total 16
1236234 8 -rw-r--r-- 1 tboisnie tboisnie 6312 Apr 22 23:01 render_file.c
1236235 4 -rw-r--r-- 1 tboisnie tboisnie 3039 Apr 22 23:01 render_folder.c
1236236 4 -rw-r--r-- 1 tboisnie tboisnie 2167 Apr 22 23:01 render_set_columns_sizes.c

./srcs/sort:
total 28
1236244 4 -rw-r--r-- 1 tboisnie tboisnie 722 Apr 22 23:01 get_compare_func.c
1236238 4 -rw-r--r-- 1 tboisnie tboisnie 439 Apr 22 23:01 compare_by_atime.c
1236239 4 -rw-r--r-- 1 tboisnie tboisnie 439 Apr 22 23:01 compare_by_ctime.c
1236240 4 -rw-r--r-- 1 tboisnie tboisnie 439 Apr 22 23:01 compare_by_mtime.c
1236243 4 -rw-r--r-- 1 tboisnie tboisnie 356 Apr 22 23:01 compare_by_type.c
1236242 4 -rw-r--r-- 1 tboisnie tboisnie 340 Apr 22 23:01 compare_by_size.c
1236241 4 -rw-r--r-- 1 tboisnie tboisnie 277 Apr 22 23:01 compare_by_name.c
```

## Author

- [BOISNIER Thomas](https://github.com/TBoisnie)
