/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_mult_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 21:51:45 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 21:39:48 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/string/string.h"
#include "libft/memory/memory.h"
#include "parser.h"

char	*remove_mult_space(char *str)
{
	char	*copy;
	char	*cursor;
	size_t	len;

	if (!(copy = str_dup(str)))
	{
		io_put_err("Remove_mult_space: str_dup() failed.");
		return (NULL);
	}
	cursor = copy;
	while (*cursor != '\0')
	{
		if (*cursor == ' ' && *(cursor + 1) == ' ')
			mem_move(cursor, cursor + 1, str_length(cursor));
		else
			++cursor;
	}
	if (*copy == ' ')
		mem_move(copy, copy + 1, str_length(copy));
	len = str_length(copy);
	if (len > 0 && copy[len - 1] == ' ')
		copy[len - 1] = '\0';
	return (copy);
}
