/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 23:15:38 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/03 16:38:10 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/io/io.h"
#include "libft/char/char.h"
#include "libft/string/string.h"
#include "parser.h"

static int	is_end(char *cursor, char *message)
{
	if (*cursor == '\0')
	{
		io_put_err(message);
		return (1);
	}
	return (0);
}

static char	*handle_squote(char *cursor)
{
	while (*cursor != '\'' && *cursor != '\0')
		cursor++;
	if (is_end(cursor, "Parser_get_next: Missing single quote (')."))
		return (NULL);
	return (++cursor);
}

static char	*handle_dquote(char *cursor, char *str)
{
	while ((*cursor != '\"' || get_bs_count(str, cursor - 1) % 2 == 1)
		&& *cursor != '\0')
		cursor++;
	if (is_end(cursor, "Parser_get_next: Missing double quote (\")."))
		return (NULL);
	return (++cursor);
}

static char	*handle_bs(char *cursor)
{
	if (is_end(cursor, "Parser_get_next: Invalid escape (\\)."))
		return (NULL);
	return (++cursor);
}

char		*parser_get_next(char *str)
{
	char	*cursor;

	cursor = str;
	while (cursor)
	{
		if (*cursor == '\0')
			break ;
		if (*cursor == ';')
		{
			++cursor;
			while (char_is_space(*cursor))
				++cursor;
			break ;
		}
		else if (*cursor == '\\' && !(cursor = handle_bs(cursor + 1)))
			break ;
		else if (*cursor == '\'' && !(cursor = handle_squote(cursor + 1)))
			break ;
		else if (*cursor == '\"' && !(cursor = handle_dquote(cursor + 1, str)))
			break ;
		else if (*cursor && !str_chr("\\\'\";", *cursor))
			cursor++;
	}
	return (cursor);
}
