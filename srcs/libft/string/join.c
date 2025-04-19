/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:27:55 by tboisnie          #+#    #+#             */
/*   Updated: 2020/05/24 20:38:11 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "string.h"

char	*str_join(const char *str_a, const char *str_b)
{
	char	*join;
	char	*cursor;
	size_t	join_len;

	join_len = str_length(str_a) + str_length(str_b) + 1;
	if (!(join = malloc(join_len * sizeof(char))))
		return (NULL);
	cursor = join;
	while (str_a && *str_a != '\0')
		*cursor++ = *str_a++;
	while (str_b && *str_b != '\0')
		*cursor++ = *str_b++;
	*cursor = '\0';
	return (join);
}
