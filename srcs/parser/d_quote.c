/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 18:51:34 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 22:30:12 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/string/string.h"
#include "command/command.h"
#include "parser.h"

static char	*check_missing_quote(t_state *st, char *cursor)
{
	if (*cursor == '\0')
	{
		io_put_err("Parser_d_quote: Missing double quote (\").");
		st->error_code = 2;
		return (NULL);
	}
	return (cursor);
}

static char	*handle_default(t_state *st, char *cursor, char *str)
{
	char	*tmp;
	char	end;

	while (*cursor != '\0' && *cursor != '"' && *cursor != '$'
		&& !(*cursor == '\\' && str_chr("$\\`\"\n", *(cursor + 1))))
		cursor++;
	if (!check_missing_quote(st, cursor))
		return (NULL);
	tmp = st->word;
	end = *cursor;
	*cursor = '\0';
	if (!(st->word = str_join(tmp, str)))
	{
		io_put_err("Parser_d_quote: str_join() failed.");
		st->error_code = 1;
	}
	*cursor = end;
	free(tmp);
	return (st->error_code ? NULL : cursor);
}

char		*parser_d_quote(t_state *st, char *cursor, t_env env, int exit_code)
{
	char	*str;

	str = ++cursor;
	st->in_quote = 1;
	while (cursor)
	{
		str = cursor;
		if (*cursor == '$')
			cursor = parser_variable(st, cursor, env, exit_code);
		else if (*cursor == '\\' && str_chr("$\\`\"\n", *(cursor + 1)))
			cursor = parser_backslash(st, cursor);
		else
			cursor = handle_default(st, cursor, str);
		if (cursor && *cursor == '"')
		{
			st->in_quote = 0;
			cursor++;
			break ;
		}
	}
	return (cursor);
}
