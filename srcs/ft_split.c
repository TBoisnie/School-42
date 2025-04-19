/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:08:33 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/08 18:26:22 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	word_count(const char *str, char c)
{
	size_t	count;
	size_t	len;

	count = 0;
	len = 0;
	while (*str != '\0')
	{
		len = 0;
		while (*str != '\0' && *str++ != c)
			++len;
		if (len > 0)
			++count;
	}
	return (count);
}

static size_t	word_len(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		++i;
	return (i);
}

static void		clean(char **str_arr, size_t size)
{
	while (size)
		free(str_arr[size--]);
	free(str_arr);
}

char			**ft_split(const char *str, char c)
{
	char	**str_arr;
	size_t	w_count;
	size_t	w_len;
	size_t	i;

	w_count = word_count(str, c);
	if (!(str_arr = (char **)malloc((w_count + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < w_count)
	{
		w_len = word_len(str, c);
		if (w_len > 0)
		{
			if (!(str_arr[i] = ft_substr(str, 0, w_len)))
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
