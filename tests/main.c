/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 22:56:54 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/26 17:02:00 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "../srcs/libasm.h"

int	main(void)
{
	int	i;

	char 	*src[] = {
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
		"Hello World!",
		"Hello World!",
		";oawegi324q;\tnkv;oi3''3afklwfwef wefawe fwae wae34 465wf -",
		"",
		NULL
	};
	char	*dst[] = {
		malloc(30 * sizeof(char)),
		malloc(15 * sizeof(char)),
		malloc(13 * sizeof(char)),
		malloc(60 * sizeof(char)),
		malloc(1 * sizeof(char)),
		NULL
	};

	/************************************
	 *	String
	 ************************************/
	int		a, b;
	size_t	sa, sb;
	char	*s;

	// ft_strlen
	for (i = 0; src[i]; ++i)
	{
		sa = ft_strlen(src[i]);
		sb = strlen(src[i]);

		printf("(%d) ft_strlen : %s | (`%lu` == `%lu`)\n",
			i, (sa == sb) ? "OK" : "FAIL", sa, sb
		);
	}
	printf("----\n");

	// ft_strcmp
	for (i = 1; src[i]; ++i)
	{
		a = ft_strcmp(src[i - 1], src[i]);
		b = strcmp(src[i - 1], src[i]);

		printf("(%d) ft_strcmp : %s | (`%d` == `%d`)\n",
			i, (a == b) ? "OK" : "FAIL", a, b
		);
	}
	printf("----\n");

	// ft_strcpy
	for (i = 0; src[i]; ++i)
	{
		s = ft_strcpy(dst[i], src[i]);

		printf("(%d) ft_strcpy : %s | (%s)\n",
			i, (ft_strcmp(src[i], dst[i]) == 0) ? "OK" : "FAIL", s
		);
	}
	printf("----\n");

	// ft_strdup
	for (i = 0; src[i]; ++i)
	{
		s = ft_strdup(src[i]);

		printf("(%d) ft_strdup : %s | (%s)\n",
			i, (ft_strcmp(src[i], s) == 0) ? "OK" : "FAIL", s
		);

		free(s);
	}
	printf("----\n");

	/************************************
	 *	Input / Output
	 ************************************/
	int		fd;
	char	buffer[512];
	ssize_t	ssa, ssb;

	// ft_write
	fd = open("test.output", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	ssa = 0;
	for (i = 0; src[i]; ++i)
		ssa += ft_write(fd, src[i], ft_strlen(src[i]));
	ssa += ft_write(fd, "\0", 1);
	close(fd);

	fd = open("test.output", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	ssb = 0;
	for (i = 0; src[i]; ++i)
		ssb += write(fd, src[i], strlen(src[i]));
	ssb += write(fd, "\0", 1);
	close(fd);

	printf("(%d) ft_write : %s | (%zd == %zd)\n",
		0, (ssa == ssb) ? "OK" : "FAIL", ssa, ssb
	);

	fd = open("donotexists", O_WRONLY | O_TRUNC);
	printf("(%d) ft_write : %s | (errno == %d) | %s\n",
		-1, (fd == -1) ? "OK" : "FAIL", errno, strerror(errno)
	);

	printf("----\n");

	// ft_read
	fd = open("test.output", O_RDONLY);
	ssa = ft_read(fd, buffer, 512);
	close(fd);
	fd = open("test.output", O_RDONLY);
	ssb = read(fd, buffer, 512);
	close(fd);

	printf("(%d) ft_read : %s | (%zd == %zd)\n",
		0, (ssa == ssb) ? "OK" : "FAIL", ssa, ssb
	);

	fd = open("donotexists", O_WRONLY | O_TRUNC);
	printf("(%d) ft_read : %s | (errno == %d) | %s\n",
		-1, (fd == -1) ? "OK" : "FAIL", errno, strerror(errno)
	);

	return (0);
}