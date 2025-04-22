# Level 14

## Requirements

- IDA: (optional) https://hex-rays.com/ida-free

## Walkthrough

1. Login from the __attacker__'s machine.

	```
	ssh -p 4242 level14@192.168.1.32
	Password: 2A31L79asukciNyi8uppkEuSx
	```

1. Check files.

	```sh
	> ls -la
	total 12
	dr-x------ 1 level14 level14  100 Mar  5  2016 .
	d--x--x--x 1 root    users    340 Aug 30  2015 ..
	-r-x------ 1 level14 level14  220 Apr  3  2012 .bash_logout
	-r-x------ 1 level14 level14 3518 Aug 30  2015 .bashrc
	-r-x------ 1 level14 level14  675 Apr  3  2012 .profile

	> find / -user $USER 2> /dev/null | grep -v /proc
	/dev/pts/0
	```

1. Well... Nothing belongs to current user... The only thing we have access to, is `getflag` itself. Maybe `disassemble` it directly?

	```sh
	> gdb getflag
	...

	> (gdb) disas main
	Dump of assembler code for function main:
	0x08048946 <+0>:	push   %ebp
	0x08048947 <+1>:	mov    %esp,%ebp
	0x08048949 <+3>:	push   %ebx
	0x0804894a <+4>:	and    $0xfffffff0,%esp
	0x0804894d <+7>:	sub    $0x120,%esp
	0x08048953 <+13>:	mov    %gs:0x14,%eax
	0x08048959 <+19>:	mov    %eax,0x11c(%esp)
	0x08048960 <+26>:	xor    %eax,%eax
	0x08048962 <+28>:	movl   $0x0,0x10(%esp)
	0x0804896a <+36>:	movl   $0x0,0xc(%esp)
	0x08048972 <+44>:	movl   $0x1,0x8(%esp)
	0x0804897a <+52>:	movl   $0x0,0x4(%esp)
	0x08048982 <+60>:	movl   $0x0,(%esp)
	0x08048989 <+67>:	call   0x8048540 <ptrace@plt>
	...
	0x08048e76 <+1328>:	movl   $0x1,0x4(%esp)
	0x08048e7e <+1336>:	mov    %eax,(%esp)
	---Type <return> to continue, or q <return> to quit---
	0x08048e81 <+1339>:	call   0x80484c0 <fwrite@plt>
	0x08048e86 <+1344>:	jmp    0x8048ead <main+1383>
	0x08048e88 <+1346>:	nop
	0x08048e89 <+1347>:	mov    0x14(%esp),%eax
	0x08048e8d <+1351>:	mov    %eax,0x8(%esp)
	0x08048e91 <+1355>:	movl   $0x100,0x4(%esp)
	0x08048e99 <+1363>:	lea    0x1c(%esp),%eax
	0x08048e9d <+1367>:	mov    %eax,(%esp)
	0x08048ea0 <+1370>:	call   0x804874c <syscall_gets>
	0x08048ea5 <+1375>:	test   %eax,%eax
	0x08048ea7 <+1377>:	jne    0x8048a89 <main+323>
	0x08048ead <+1383>:	mov    $0x0,%eax
	0x08048eb2 <+1388>:	mov    0x11c(%esp),%edx
	0x08048eb9 <+1395>:	xor    %gs:0x14,%edx
	0x08048ec0 <+1402>:	je     0x8048ec7 <main+1409>
	0x08048ec2 <+1404>:	call   0x80484a0 <__stack_chk_fail@plt>
	0x08048ec7 <+1409>:	mov    -0x4(%ebp),%ebx
	0x08048eca <+1412>:	leave
	0x08048ecb <+1413>:	ret
	End of assembler dump.
	```

1. Goddammit! There is a lot a thing. Using IDA, we can generate pseudo-C code.

	```C
	int __decl main(int argc, const char **argv, const char **envp)
	{
		unsigned int v4; // eax
		int v5; // ebx
		int v6; // eax
		int v7; // ebx
		int v8; // eax
		int v9; // ebx
		int v10; // eax
		int v11; // ebx
		int v12; // eax
		int v13; // ebx
		int v14; // eax
		int v15; // ebx
		int v16; // eax
		int v17; // ebx
		int v18; // eax
		int v19; // ebx
		int v20; // eax
		int v21; // ebx
		int v22; // eax
		int v23; // ebx
		int v24; // eax
		int v25; // ebx
		int v26; // eax
		int v27; // ebx
		int v28; // eax
		double v29; // [esp+4h] [ebp-120h]
		int v30; // [esp+10h] [ebp-114h]
		int v31; // [esp+14h] [ebp-110h]
		int v32[65]; // [esp+1Ch] [ebp-108h] BYREF
		v32[64] = __readgsdword(0x14u);
		v30 = 0;
		if ( ptrace(0, 0, 1, 0) < 0 )
		{
			puts("You should not reverse this");
			return 1;
		}
		if ( getenv("LD_PRELOAD") || open("/etc/ld.so.preload", 0) > 0 )
		{
			fwrite("Injection Linked lib detected exit..\n", 1, 37, stderr);
			return 1;
		}
		v31 = syscall_open("/proc/self/maps", 0);
		if ( v31 == -1 )
		{
			fwrite("/proc/self/maps is unaccessible, probably a LD_PRELOAD attempt exit..\n", 1, 70, stderr);
			return 1;
		}
		do
		{
			do
			{
				while ( 1 )
				{
					if ( ! syscall_gets((int)v32, 256, v31) )
					{
						return 0;
					}
					if ( !isLib(v32, "libc") )
					{
						break;
					}
					v30 = 1;
				}
			}
			while ( !v30 );
			if ( isLib(v32, "ld") )
			{
				fwrite("Check flag.Here is your token : ", 1, 32, stdout);
				v4 = getuid();
				if ( v4 == 3006 )
				{
					v15 = stdout;
					v16 = ft_des("H8B8h_20B4J43><8>\\ED<;j@3");
					fputs(v16, v15);
					goto LABEL_49;
				}
				if ( v4 > 3006 )
				{
					if ( v4 == 3010 )
					{
						v19 = stdout;
						v20 = ft_des("74H9D^3ed7k05445J0E4e;Da4");
						fputs(v20, v19);
						goto LABEL_49;
					}
					if ( v4 > 3010 )
					{
						if ( v4 == 3012 )
						{
							v23 = stdout;
							v24 = ft_des("8_Dw\"4#?+3i]q&;p6 gtw88EC");
							fputs(v24, v23);
						}
						else if ( v4 < 3012 )
						{
							v21 = stdout;
							v22 = ft_des("70hCi,E44Df[A4B/J@3f<=:`D");
							fputs(v22, v21);
						}
						else if ( v4 == 3013 )
						{
							v25 = stdout;
							v26 = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
							fputs(v26, v25);
						}
						else
						{
							if ( v4 != 3014 )
								goto LABEL_48;
							v27 = stdout;
							v28 = ft_des("g <t61:|4_|!@IF.-62FH&G~DCK/Ekrvvdwz?v|");
							fputs(v28, v27);
						}
						goto LABEL_49;
					}
					if ( v4 == 3008 )
					{
						v17 = stdout;
						v18 = ft_des("bci`mC{)jxkn<\"uD~6%g7FK`7", v29);
						fputs(v18, v17);
						goto LABEL_49;
					}
					v11 = stdout;
					if ( v4 > 3008 )
						v12 = ft_des("Dc6m~;}f8Cj#xFkel;#&ycfbK");
					else
						v12 = ft_des("78H:J4<4<9i_I4k0J^5>B1j`9");
				}
				else
				{
					if ( v4 == 3002 )
					{
						v9 = stdout;
						v10 = ft_des("<>B16\\AD<C6,G_<1>^7ci>l4B");
						fputs(v10, v9);
						goto LABEL_49;
					}
					if ( v4 <= 3002 )
					{
						if ( v4 == 3000 )
						{
							v5 = stdout;
							v6 = ft_des("I`fA>_88eEd:=`85h0D8HE>,D");
							fputs(v6, v5);
						}
						else if ( v4 > 3000 )
						{
							v7 = stdout;
							v8 = ft_des("7`4Ci4=^d=J,?>i;6,7d416,7");
							fputs(v8, v7);
						}
						else
						{
							if ( v4 )
							{
								LABEL_48:
								fwrite("\nNope there is no token here for you sorry. Try again :)", 1, 56, stdout);
								goto LABEL_49;
							}
							fwrite("You are root are you that dumb ?\n", 1, 33, stdout);
						}

					LABEL_49:
						fputc(10, stdout);
						return 0;
					}
					if ( v4 == 3004 )
					{
						v13 = stdout;
						v14 = ft_des("?4d@:,C>8C60G>8:h:Gb4?l,A");
						fputs(v14, v13);
						goto LABEL_49;
					}
					v11 = stdout;
					if ( v4 > 3004 )
						v12 = ft_des("G8H.6,=4k5J0<cd/D@>>B:>:4");
					else
						v12 = ft_des("B8b:6,3fj7:,;bh>D@>8i:6@D");
				}
				fputs(v12, v11);
				goto LABEL_49;
			}
		}
		while ( afterSubstr(v32, "00000000 00:00 0") );

		fwrite("LD_PRELOAD detected through memory maps exit ..\n", 1, 48, stderr);

		return 0;
	}
	```

1. Well, it's easier to read/understand, but let's refactor it first to remove boilerplate.

	```C
	int __decl main(int argc, const char **argv, const char **envp)
	{
		int flag; // eax
		int buffer[65]; // [esp+1Ch] [ebp-108h] BYREF

		buffer[64] = __readgsdword(0x14u);

		if ( ptrace(0, 0, 1, 0) < 0 )
		{
			puts("You should not reverse this");
			return 1;
		}

		if ( getenv("LD_PRELOAD") || open("/etc/ld.so.preload", 0) > 0 )
		{
			fwrite("Injection Linked lib detected exit..\n", 1, 37, stderr);
			return 1;
		}

		int maps = syscall_open("/proc/self/maps", 0);

		if ( maps == -1 )
		{
			fwrite("/proc/self/maps is unaccessible, probably a LD_PRELOAD attempt exit..\n", 1, 70, stderr);
			return 1;
		}

		do
		{
			int done = 0;

			do
			{
				while ( 1 )
				{
					if ( ! syscall_gets((int)buffer, 256, maps) )
						return 0;
					if ( ! isLib(buffer, "libc") )
						break;
					done = 1;
				}
			}
			while ( ! done );

			if ( isLib(buffer, "ld") )
			{
				fwrite("Check flag.Here is your token : ", 1, 32, stdout);
				unsigned int uid = getuid();

				if ( uid == 3006 ) // Flag 6
				{
					fputs(ft_des("H8B8h_20B4J43><8>\\ED<;j@3"), stdout);
					goto QUIT;
				}

				if ( uid > 3006 )
				{
					if ( uid == 3010 ) // Flag 10
					{
						fputs(ft_des("74H9D^3ed7k05445J0E4e;Da4"), stdout);
						goto QUIT;
					}

					if ( uid > 3010 )
					{
						if ( uid == 3012 ) // Flag 12
							fputs(ft_des("8_Dw\"4#?+3i]q&;p6 gtw88EC"), stdout);
						else if ( uid < 3012 ) // Flag 11
							fputs(ft_des("70hCi,E44Df[A4B/J@3f<=:`D"), stdout);
						else if ( uid == 3013 ) // Flag 13
							fputs(ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I"), stdout);
						else
						{
							if ( uid != 3014 ) // Flag 14
								goto FAILED;
							fputs(ft_des("g <t61:|4_|!@IF.-62FH&G~DCK/Ekrvvdwz?v|"), stdout);
						}
						goto QUIT;
					}

					if ( uid == 3008 ) // Flag 8
					{
						double v29;
						fputs(ft_des("bci`mC{)jxkn<\"uD~6%g7FK`7", v29), stdout);
						goto QUIT;
					}

					if ( uid > 3008 ) // Flag 9
						flag = ft_des("Dc6m~;}f8Cj#xFkel;#&ycfbK");
					else // Flag 7
						flag = ft_des("78H:J4<4<9i_I4k0J^5>B1j`9");
				}
				else
				{
					if ( uid == 3002 ) // Flag 2
					{
						fputs(ft_des("<>B16\\AD<C6,G_<1>^7ci>l4B"), stdout);
						goto QUIT;
					}

					if ( uid <= 3002 )
					{
						if ( uid == 3000 ) // Flag 0
							fputs(ft_des("I`fA>_88eEd:=`85h0D8HE>,D"), stdout);
						else if ( uid > 3000 ) // Flag 1
							fputs(ft_des("7`4Ci4=^d=J,?>i;6,7d416,7"), stdout);
						else
						{
							if ( uid )
							{
	FAILED:
								fwrite("\nNope there is no token here for you sorry. Try again :)", 1, 56, stdout);
								goto QUIT;
							}
							fwrite("You are root are you that dumb ?\n", 1, 33, stdout);
						}
	QUIT:
						fputc(10, stdout);
						return 0;
					}

					if ( uid == 3004 ) // Flag 4
					{
						fputs(ft_des("?4d@:,C>8C60G>8:h:Gb4?l,A"), stdout);
						goto QUIT;
					}

					if ( uid > 3004 ) // Flag 5
						flag = ft_des("G8H.6,=4k5J0<cd/D@>>B:>:4");
					else // Flag 3
						flag = ft_des("B8b:6,3fj7:,;bh>D@>8i:6@D");
				}

				fputs(flag, stdout);
				goto QUIT;
			}
		}
		while ( afterSubstr(buffer, "00000000 00:00 0") );

		fwrite("LD_PRELOAD detected through memory maps exit ..\n", 1, 48, stderr);
		return 0;
	}
	```

1. Amazing! Just following the logic, we can determine that it is just a bunch of `if/else` conditions on the `getuid`. So let's just try the same method we used previously (aka. override `getuid` returned value).

	```sh
	> gdb getflag
	...

	> (gdb) b getuid
	Breakpoint 1 at 0x80484b0

	> (gdb) run
	Starting program: /bin/getflag
	You should not reverse this
	[Inferior 1 (process 2686) exited with code 01]
	```

1. Screw you! Where does this come from ? Using our previous code, we can see that the guilty one is `ptrace`.

	```C
	if ( ptrace(0, 0, 1, 0) < 0 )
	{
		puts("You should not reverse this");
		return 1;
	}
	```

1. Ahah! Same *BIP*, let's override it's returned value...

	```sh
	> gdb getflag
	...

	# Set breakpoint for `ptrace` and `getuid`
	> b ptrace
	Breakpoint 1 at 0x8048540
	> b getuid
	Breakpoint 2 at 0x80484b0

	# Execute
	> (gdb) run
	Starting program: /bin/getflag

	Breakpoint 1, 0xb7f146d0 in ptrace () from /lib/i386-linux-gnu/libc.so.6

	# Execute instructions one by one until `ptrace` returns
	> (gdb) step
	Single stepping until exit from function ptrace, which has no line number information.
	0x0804898e in main ()
	> (gdb) set $eax=0
	> (gdb) c
	Continuing.

	Breakpoint 2, 0xb7ee4cc0 in getuid () from /lib/i386-linux-gnu/libc.so.6

	# Same thing, but for `getuid` (3014 is found from previous source code and seen in level01 /etc/passwd)
	> (gdb) step
	Single stepping until exit from function getuid, which has no line number information.
	0x08048b02 in main ()
	> (gdb) set $eax=3014
	> (gdb) c
	Continuing.
	Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
	[Inferior 1 (process 2737) exited normally]
	```

## Documentation

- Function: [ptrace](https://man7.org/linux/man-pages/man2/ptrace.2.html)
