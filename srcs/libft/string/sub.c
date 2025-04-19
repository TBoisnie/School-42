/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:21:47 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:25:36 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "string.h"

char	*str_sub(char const *str, unsigned int start, size_t length)
{
	char	*sub;
	size_t	i;
	size_t	str_len;

	str_len = str_length(str);
	if (start >= str_len)
		length = 0;
	else if (start + length > str_len)
		length = str_len - start;
	if (!(sub = malloc((length + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < length && str[start + i] != '\0')
	{
		sub[i] = str[start + i];
		++i;
	}
	sub[i] = '\0';
	return (sub);
}
