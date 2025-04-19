/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 21:10:08 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 21:39:51 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/char/char.h"
#include "libft/io/io.h"
#include "parser.h"

char	*parser_redirect_in(t_state *st, char *cursor)
{
	if (st->file_in)
	{
		st->file_in = 2;
		st->error_code = 1;
		io_put_err("Parser_redirect_in: Invalid input file.");
		return (NULL);
	}
	if (st->file_out)
	{
		st->file_out = 2;
		st->error_code = 1;
		io_put_err("Parser_redirect_in: Invalid output file.");
		return (NULL);
	}
	cursor++;
	st->file_in = 1;
	while (char_is_space(*cursor))
		cursor++;
	return (cursor);
}
