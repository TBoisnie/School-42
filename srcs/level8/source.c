#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
