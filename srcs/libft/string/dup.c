/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 19:00:13 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:25:22 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "string.h"

char	*str_dup(const char *str)
{
	char	*dup;
	size_t	str_len;

	str_len = str_length(str) + 1;
	if (!(dup = malloc(str_len * sizeof(char))))
		return (NULL);
	while (str_len--)
		dup[str_len] = str[str_len];
	return (dup);
}
