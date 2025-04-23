#include <string.h>
#include <stdlib.h>
#include "malloc.h"

int main()
{
	char * str_1 = malloc(42);
	strcpy(str_1, "Hello\nWorld !\n");
	char * str_2 = malloc(6);
	strcpy(str_2, "Hello");
	char * str_3 = malloc(1024);
	strcpy(str_3+1000, "Hi! What's up?");
	strcpy(str_3+1000, "MySecretPassword");
	show_alloc_mem_ex();
	return (0);
}
