/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 20:51:26 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:28:00 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../memory/memory.h"
#include "string.h"

static char	*get_space(char *str, const char *find, const char *replace)
{
	size_t	count;
	char	*found;

	count = 0;
	found = str;
	while ((found = str_n_str(found, find, str_length(found))))
	{
		count++;
		found = found + str_length(find);
	}
	return (mem_calloc(
		str_length(str) + count * (str_length(replace) - str_length(find)) + 1,
		sizeof(char)));
}

char		*str_replace(char *str, const char *find, const char *replace)
{
	char	*ret;
	char	*cursor;
	char	*found;

	if (!(ret = get_space(str, find, replace)))
		return (NULL);
	found = str;
	cursor = ret;
	while ((found = str_n_str(found, find, str_length(found))))
	{
		cursor = mem_copy(cursor, str, found - str);
		cursor = mem_copy(cursor, replace, str_length(replace));
		found += str_length(find);
		str = found;
	}
	mem_copy(cursor, str, str_length(str));
	return (ret);
}
