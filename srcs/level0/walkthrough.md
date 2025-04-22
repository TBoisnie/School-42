# Level 0

## Requirements

- [Ida](https://hex-rays.com/ida-free/)

## Walkthrough

1. Login

	```sh
	> ssh -p 4242 level0@192.168.1.66
	Password: level0

	GCC stack protector support:            Enabled
	Strict user copy checks:                Disabled
	Restrict /dev/mem access:               Enabled
	Restrict /dev/kmem access:              Enabled
	grsecurity / PaX: No GRKERNSEC
	Kernel Heap Hardening: No KERNHEAP
	System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
	RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
	No RELRO        No canary found   NX enabled    No PIE          No RPATH   No RUNPATH   /home/user/level0/level0
	```

1. Lot of informations there... Need to do some research...

	```
	- `/dev/mem` - Provides access to the system's physical memory.
	- `/dev/kmem` - Provides access to the system's virtual memory.
	- `grsecurity / PaX` - grsecurity est une modification augmentant la sécurité pour le noyau Linux distribué sous la licence publique générale GNU version 2. Il inclut différents éléments, dont PaX, un système de contrôle d'accès à base de rôles et différents moyens de renforcer la sécurité générale du noyau.
	- `ASLR` - Address Space Layout Randomization (ASLR) is a security technique used in operating systems to randomize the memory addresses used by system and application processes. By doing so, it makes it significantly harder for an attacker to predict the location of specific processes and data, such as the stack, heap, and libraries, thereby mitigating certain types of exploits, particularly buffer overflows.
	- `NX` - The No-Execute (NX) bit, also known as Execute Disable (XD) in Intel terminology, is a hardware-based security feature designed to mitigate the effects of buffer overflow attacks. When implemented and enabled, it distinguishes between memory regions that are intended for executable code and those meant for data, such as the stack and heap. The core idea is to prevent an attacker from executing malicious code through buffer overflow vulnerabilities by putting the malicious code in the stack for example and directing the execution flow to it.
	- `PIE` - A binary compiled as PIE, or Position Independent Executable, means the program can load at different memory locations each time it's executed, preventing hardcoded addresses.
	```

1. Fine. Now we have a better understanding, let's try to run it.

	```sh
	> ./level0
	Segmentation fault (core dumped)
	```

1. Amazing, dev at its pick right there.

	```sh
	> ./level0 qwe
	No !
	```

1. Better, but not what we want. Maybe a quick `strings` check will help us.

	```sh
	> strings level0
	-bash: /usr/bin/strings: Input/output error
	```

1. Nevermind... I'm done... Let's just copy and disassemble it.

	```sh
	# In a new Host Terminal
	> echo $PWD
	~/RainFall/level0

	> mkdir Ida

	> scp -P 4242 level0@192.168.1.66:~/level0 ./Ida/level0
	Password: level0
	```

1. Open `level0` file with Ida, then from the functions list, go to `main`. Now, we can use `Pseudocode generator (F5)` to get some C code. Then after some renaming, we get something like :

	```c
	int __cdecl main(int argc, const char **argv, const char **envp)
	{
		char *args[2]; // [esp+10h] [ebp-10h] BYREF
		int uid; // [esp+18h] [ebp-8h]
		int gid; // [esp+1Ch] [ebp-4h]

		if ( atoi(argv[1]) == 423 )
		{
			args[0] = (char *)strdup("/bin/sh");
			args[1] = 0;
			gid = getegid();
			uid = geteuid();
			setresgid(gid, gid, gid);
			setresuid(uid, uid, uid);
			execv("/bin/sh", args);
		}
		else
		{
			fwrite("No !\n", 1, 5, stderr);
		}
		return 0;
	}
	```

1. As we can we see, an `execv` calls is made to `/bin/sh`, but it's "guarded" by an `atoi` call with `argv[1]` a.k.a. the first arguments provided when we run the program. Fine ! What's the expected value from this `atoi` call ? `423` ? Perfect, let's do it.

	```sh
	> ./level0 423
	$
	```

1. Easy(-e), we now have a Shell! Play with it.

	```sh
	$ echo $PWD
	/home/user/level0

	$ echo $USER
	level0

	$ whoami
	level1
	```

1. Ah! We have our target's right. We should be able to access the `.pass` file now. Get the flag.

	```sh
	$ cat /home/user/level1/.pass
	1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
	```

## Documentation

- Tech: [ASLR](https://book.hacktricks.xyz/binary-exploitation/common-binary-protections-and-bypasses/aslr)
- Tech: [Relro](https://book.hacktricks.xyz/binary-exploitation/common-binary-protections-and-bypasses/relro)
- Tech: [NX](https://book.hacktricks.xyz/binary-exploitation/common-binary-protections-and-bypasses/no-exec-nx)
- Tech: [PIE](https://book.hacktricks.xyz/binary-exploitation/common-binary-protections-and-bypasses/pie)
- Tech: [rpath](https://en.wikipedia.org/wiki/Rpath)
- Vulnerability: [rpath](https://book.hacktricks.xyz/linux-hardening/privilege-escalation#rpath)
- Software: [IDA Free](https://hex-rays.com/ida-free/)
