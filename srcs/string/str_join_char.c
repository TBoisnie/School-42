/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 06:23:41 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:14:25 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cube3d.h"
#include "string.h"

char	*str_join_char(char *str, char c)
{
	char	*join;
	char	*cursor;
	size_t	str_len;

	str_len = 0;
	while (str && str[str_len])
		++str_len;
	if (!(join = (char *)malloc((str_len + 2) * sizeof(char))))
		exit_error("Error\n`str_join_char` malloc failed.");
	cursor = join;
	while (str && *str)
		*cursor++ = *str++;
	*cursor++ = c;
	*cursor = '\0';
	return (join);
}
