/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 21:51:45 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 21:39:48 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/char/char.h"
#include "parser.h"

char	*parser_redirect_out(t_state *st, char *cursor)
{
	if (st->file_in)
	{
		st->file_in = 2;
		st->error_code = 1;
		io_put_err("Parser_redirect_out: Invalid input file.");
		return (NULL);
	}
	if (st->file_out)
	{
		st->file_out = 2;
		st->error_code = 1;
		io_put_err("Parser_redirect_out: Invalid output file.");
		return (NULL);
	}
	st->file_out = 1;
	if (*++cursor == '>')
	{
		st->append = 1;
		cursor++;
	}
	while (char_is_space(*cursor))
		cursor++;
	return (cursor);
}
