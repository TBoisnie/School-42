#include <stdio.h>
#include <stdlib.h>

int m;

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

int main(int argc, const char **argv, const char **envp)
{
	return v();
}
