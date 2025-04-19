/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:35:32 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 20:37:22 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_n_str(const char *str, const char *to_find, size_t length)
{
	size_t	i;
	size_t	j;

	if (*to_find == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i < length)
	{
		if (str[i] == to_find[0])
		{
			j = 1;
			while (to_find[j] != '\0' && str[i + j] == to_find[j]
				&& (i + j) < length)
			{
				++j;
			}
			if (to_find[j] == '\0')
				return ((char *)&str[i]);
		}
		++i;
	}
	return (NULL);
}
