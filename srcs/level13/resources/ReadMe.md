# Level 13

## Requirements

- None

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level13@192.168.1.32
	Password: g1qKMiRpXf53AWhDaU7FEkczr
	```

1. Check files.

	```sh
	> ls -l
	total 8
	-rwsr-sr-x 1 flag13 level13 7303 Aug 30  2015 level13
	```

1. Run it.

	```sh
	> ./level13
	UID 2013 started us but we we expect 4242
	```

1. Ok, so it's going to be an UID issue ? Let's do our usual `strings` check.

	```sh
	> strings level13
	...
	exit
	strdup
	printf
	getuid
	...
	0123456
	UID %d started us but we we expect %d
	boe]!ai0FB@.:|L6l@A?>qJ}I
	your token is %s
	...
	ft_des
	...
	```

1. As expected, there is a call to `getuid`. But we can also notice that we have a string that looks like a hashed token, which could have been done with the `ft_des` (ft_* is standard function prefix from 42-School). What does the `getuid` documentation says ?

	```
	- `getuid` - returns the real user ID of the calling process.
	```

1. Ok, so far, we could try to find to which user belongs to UID 4242.

	```sh
	> cat /etc/passwd | grep 4242
	```

1. Hum... Nothing about 4242 ? There is no way we find an exploit of `getuid` then...
Let's decompile it to check what is happening.

	```sh
	> gdb level13
	GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
	...

	> (gdb) disas main
	Dump of assembler code for function main:
	0x0804858c <+0>:	push   %ebp
	0x0804858d <+1>:	mov    %esp,%ebp
	0x0804858f <+3>:	and    $0xfffffff0,%esp
	0x08048592 <+6>:	sub    $0x10,%esp
	0x08048595 <+9>:	call   0x8048380 <getuid@plt>
	0x0804859a <+14>:	cmp    $0x1092,%eax
	0x0804859f <+19>:	je     0x80485cb <main+63>
	0x080485a1 <+21>:	call   0x8048380 <getuid@plt>
	0x080485a6 <+26>:	mov    $0x80486c8,%edx
	0x080485ab <+31>:	movl   $0x1092,0x8(%esp)
	0x080485b3 <+39>:	mov    %eax,0x4(%esp)
	0x080485b7 <+43>:	mov    %edx,(%esp)
	0x080485ba <+46>:	call   0x8048360 <printf@plt>
	0x080485bf <+51>:	movl   $0x1,(%esp)
	0x080485c6 <+58>:	call   0x80483a0 <exit@plt>
	0x080485cb <+63>:	movl   $0x80486ef,(%esp)
	0x080485d2 <+70>:	call   0x8048474 <ft_des>
	0x080485d7 <+75>:	mov    $0x8048709,%edx
	0x080485dc <+80>:	mov    %eax,0x4(%esp)
	0x080485e0 <+84>:	mov    %edx,(%esp)
	0x080485e3 <+87>:	call   0x8048360 <printf@plt>
	0x080485e8 <+92>:	leave
	0x080485e9 <+93>:	ret
	End of assembler dump.
	```

	```C
	int __cdecl main(int argc, const char **argv, const char **envp)
	{
		int v3; // eax
		const char *v4; // eax

		if ( getuid() != 4242 )
		{
			v3 = getuid();
			printf("UID %d started us but we we expect %d\n", v3, 4242);
			exit(1);
		}

		v4 = (const char *)ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");

		return printf("your token is %s\n", v4);
	}
	```

1. Ok, it's clearer. Our first intuition was right, `getuid` is our target, but since there is not any user with UID = 4242, we have to find a way to force it ourselves. After some research, we find out that we can modify a function return value using GDB.

	```sh
	> gdb level13
	...

	# Add a breakpoint on `getuid`
	> (gdb) b getuid
	Breakpoint 1 at 0x8048380

	# Start the program
	> (gdb) run
	Starting program: /home/user/level13/level13

	Breakpoint 1, 0xb7ee4cc0 in getuid () from /lib/i386-linux-gnu/libc.so.6

	# Execute instructions one by one until `getuid` returns
	> (gdb) step
	Single stepping until exit from function getuid, which has no line number information.
	0x0804859a in main ()

	# Check `getuid` returned value
	> (gdb) p $eax
	$2 = 2013

	# Great, now override it
	> (gdb) set $eax=4242

	# Continue
	> (gdb) c
	Continuing.
	your token is 2A31L79asukciNyi8uppkEuSx
	```

## Documentation

- Function: [getuid](https://man7.org/linux/man-pages/man2/getuid.2.html)
- Exploit: [Modify function return value](https://www.opensourceforu.com/2011/08/modify-function-return-value-hack-part-1/)
