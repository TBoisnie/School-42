/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 15:18:50 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 22:37:06 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/string/string.h"
#include "libft/io/io.h"
#include "parser.h"

char	*parser_backslash(t_state *st, char *cursor)
{
	char	*tmp;
	char	end;

	cursor++;
	if (*cursor == '\0')
	{
		io_put_err("Parser_backslash: Invalid escape (\\).");
		st->error_code = 2;
		return (NULL);
	}
	end = *++cursor;
	*cursor-- = '\0';
	tmp = st->word;
	if (!(st->word = str_join(tmp, cursor)))
	{
		io_put_err("Parser_backslash: str_join() failed.");
		st->error_code = 1;
		*++cursor = end;
		free(tmp);
		return (NULL);
	}
	*++cursor = end;
	free(tmp);
	return (cursor);
}
