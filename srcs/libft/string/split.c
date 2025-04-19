/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:04:02 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:33:30 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "string.h"

static size_t	word_count(const char *str, char separator)
{
	size_t	count;
	size_t	len;

	count = 0;
	len = 0;
	while (*str != '\0')
	{
		len = 0;
		while (*str != '\0' && *str++ != separator)
			++len;
		if (len > 0)
			++count;
	}
	return (count);
}

static size_t	word_len(const char *str, char separator)
{
	size_t	i;

	i = 0;
	while (str[i] != separator && str[i] != '\0')
		++i;
	return (i);
}

static void		clean(char **str_arr, size_t size)
{
	while (size)
		free(str_arr[size--]);
	free(str_arr);
}

static char		**populate(char **str_arr, size_t w_count, const char *str,
							char separator)
{
	size_t	w_len;
	size_t	i;

	i = 0;
	while (i < w_count)
	{
		w_len = word_len(str, separator);
		if (w_len > 0)
		{
			if (!(str_arr[i] = str_sub(str, 0, w_len)))
			{
				clean(str_arr, i);
				return (NULL);
			}
			++i;
		}
		str += w_len + 1;
	}
	str_arr[i] = NULL;
	return (str_arr);
}

char			**str_split(const char *str, char separator)
{
	char	**str_arr;
	size_t	w_count;

	if (!str)
		return (NULL);
	w_count = word_count(str, separator);
	if (!(str_arr = malloc((w_count + 1) * sizeof(char *))))
		return (NULL);
	str_arr = populate(str_arr, w_count, str, separator);
	return (str_arr);
}
