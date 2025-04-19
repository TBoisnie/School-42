/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 19:19:38 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 22:40:01 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/char/char.h"
#include "parser.h"

char	*parser_pipe(t_cmd *left, t_state *st, char *cursor)
{
	cursor++;
	while (char_is_space(*cursor))
		cursor++;
	if (*cursor == ';' || *cursor == '|' || *cursor == '\0')
	{
		io_put_err("Parser_pipe: Empty pipe.");
		st->error_code = 2;
		return (NULL);
	}
	if (!(left->piped = cmd_new()))
	{
		io_put_err("Parser_pipe: cmd_new() failed.");
		st->error_code = 1;
		return (NULL);
	}
	left->piped->exit_code = left->exit_code;
	return (cursor);
}
