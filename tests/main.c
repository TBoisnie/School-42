#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
// #include "../srcs/get_next_line.h"
#include "../srcs/get_next_line_bonus.h"

int	main(void)
{
	char *line;
	int	result = 1;

	char *files[] = {
		"resources/test_4.txt",
		"resources/test_3.txt",
		"resources/test_2.txt",
		"resources/test_1.txt",
		NULL
	};
	int fd[10] = {0};

	int opened = 0;

	while (files[opened] != NULL)
	{
		fd[opened] = open(files[opened], O_RDONLY);
		++opened;
	}

	int i = 0;
	int active = opened;

	while (active > 0)
	{
		if (fd[i % opened] > 0)
		{
			printf("----- Reading file `%s` -----\n", files[i % opened]);
			result = get_next_line(fd[i % opened], &line);
			printf("-- Result = `%d`\n", result);
			if (result >= 0)
			{
				if (line)
					printf("-- Line = \n`%s`\n", line);
				free(line);
				if (result == 0)
				{
					printf("----- End of File -----\n");

					close(fd[i % opened]);
					fd[i % opened] = 0;
					--active;
				}
			}
			else
			{
				printf("----- Error -----\n");

				close(fd[i % opened]);
				fd[i % opened] = 0;
				--active;
			}
		}
		++i;
	}

	do
	{
		printf("----- Reading stdin -----\n");
		result = get_next_line(0, &line);
		printf("-- Result = `%d`\n", result);
		if (result > 0)
		{
			printf("-- Line = \n`%s`\n", line);
			free(line);
		}
		else
		{
			if (result == 0)
				printf("----- End of File -----\n");
			else
				printf("----- Error -----\n");
		}

	} while (result > 0);

	return (0);
}
