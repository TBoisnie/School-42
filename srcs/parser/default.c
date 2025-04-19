/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 20:25:29 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 22:30:05 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/char/char.h"
#include "libft/string/string.h"
#include "parser.h"

char	*parser_default(t_state *st, char *cursor)
{
	char	*str;
	char	*tmp;
	char	end;

	str = cursor;
	while (!str_chr("|><$;\\\'\"", *cursor) && !char_is_space(*cursor)
		&& *cursor != '\0')
		cursor++;
	end = *cursor;
	*cursor = '\0';
	tmp = st->word;
	if (!(st->word = str_join(tmp, str)))
	{
		io_put_err("Parser_default: str_join() failed.");
		st->error_code = 1;
		*cursor = end;
		free(tmp);
		return (NULL);
	}
	*cursor = end;
	free(tmp);
	return (cursor);
}
