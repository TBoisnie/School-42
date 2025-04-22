#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
