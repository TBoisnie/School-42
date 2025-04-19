/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 19:13:38 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 21:39:36 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/string/string.h"
#include "parser.h"

static char	*check_missing_quote(t_state *st, char *cursor)
{
	if (*cursor == '\0')
	{
		io_put_err("Parser_s_quote: Missing single quote (').");
		st->error_code = 2;
		return (NULL);
	}
	return (cursor);
}

char		*parser_s_quote(t_state *st, char *cursor)
{
	char	*str;
	char	*tmp;
	char	end;

	str = ++cursor;
	while (*cursor != '\'' && *cursor != '\0')
		cursor++;
	if (!check_missing_quote(st, cursor))
		return (NULL);
	tmp = st->word;
	end = *cursor;
	*cursor = '\0';
	if (!(st->word = str_join(tmp, str)))
	{
		io_put_err("Parser_s_quote: str_join() failed.");
		st->error_code = 1;
		*cursor = end;
		free(tmp);
		return (NULL);
	}
	*cursor++ = end;
	free(tmp);
	return (cursor);
}
