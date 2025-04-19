/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_int_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:39:59 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:13:50 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cube3d.h"
#include "string.h"

static size_t	int_length(int number, size_t base_length)
{
	size_t	length;

	length = 1;
	while ((number /= base_length))
		++length;
	return (length);
}

char			*str_from_int_base(int number, char *base)
{
	size_t	base_len;
	size_t	int_len;
	char	*str;

	base_len = str_length(base);
	int_len = int_length(number, base_len);
	if (!(str = malloc((int_len + 1) * sizeof(char))))
		exit_error("Error\nString - Sfib (malloc).");
	str[int_len] = '\0';
	while (int_len-- > 0)
	{
		str[int_len] = base[number % base_len];
		number /= base_len;
	}
	return (str);
}
