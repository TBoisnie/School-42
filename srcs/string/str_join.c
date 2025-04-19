/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 06:23:41 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:14:32 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cube3d.h"
#include "string.h"

char	*str_join(char *str_a, char *str_b)
{
	char	*join;
	char	*cursor;
	size_t	str_a_len;
	size_t	str_b_len;

	str_a_len = 0;
	while (str_a && str_a[str_a_len])
		++str_a_len;
	str_b_len = 0;
	while (str_b && str_b[str_b_len])
		++str_b_len;
	if (!(join = (char *)malloc((str_a_len + str_b_len + 1) * sizeof(char))))
		exit_error("Error\n`str_join` malloc failed.");
	cursor = join;
	while (str_a && *str_a)
		*cursor++ = *str_a++;
	while (str_b && *str_b)
		*cursor++ = *str_b++;
	*cursor = '\0';
	return (join);
}
