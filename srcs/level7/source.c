#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
