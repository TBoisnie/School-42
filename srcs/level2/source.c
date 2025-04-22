#include <stdio.h>
#include <string.h>

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

int __cdecl main(int argc, const char **argv, const char **envp)
{
	return p();
}
