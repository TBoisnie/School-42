#include <stdio.h>
#include <string.h>

char * p(char * input, char * separator)
{
	char chunk[4104]; // [esp+10h] [ebp-1008h] BYREF

	puts(separator);
	read(0, chunk, 4096);

	*strchr(chunk, '\n') = '\0';

	return strncpy(input, chunk, 20);
}

char * pp(char * buffer)
{
	char input_1[20]; // [esp+28h] [ebp-30h] BYREF
	char input_2[28]; // [esp+3Ch] [ebp-1Ch] BYREF

	p(input_1, " - ");
	p(input_2, " - ");

	strcpy(buffer, input_1);

	buffer[strlen(buffer)] = ' ';

	return strcat(buffer, input_2);
}

int main(int argc, const char **argv, const char **envp)
{
	char buffer[42]; // [esp+16h] [ebp-2Ah] BYREF

	pp(buffer);
	puts(buffer);

	return 0;
}
