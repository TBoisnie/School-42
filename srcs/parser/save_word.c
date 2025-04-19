/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 22:02:42 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 21:39:40 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/string/string.h"
#include "separator/separator.h"
#include "parser.h"

static t_cmd	*save_in(t_cmd *cmd, t_state *st)
{
	free(cmd->file_in);
	cmd->file_in = st->word;
	st->file_in = FALSE;
	return (cmd);
}

static t_cmd	*save_out(t_cmd *cmd, t_state *st)
{
	free(cmd->file_out);
	cmd->file_out = st->word;
	st->file_out = FALSE;
	cmd->append = st->append;
	st->append = FALSE;
	redirect_out(cmd, 0);
	return (cmd);
}

t_cmd			*parser_save_word(t_cmd *cmd, t_state *st)
{
	if (!st->word)
		return (cmd);
	if (st->file_in)
		cmd = save_in(cmd, st);
	else if (st->file_out)
		cmd = save_out(cmd, st);
	else if (!cmd->name)
	{
		cmd->name = st->word;
		if (!(st->word = str_dup(st->word)))
		{
			io_put_err("Parser_save_word: str_dup() failed.");
			st->error_code = 1;
			return (NULL);
		}
		cmd = cmd_arg_add(cmd, st->word);
	}
	else
		cmd = cmd_arg_add(cmd, st->word);
	st->word = NULL;
	if (!cmd)
		st->error_code = 1;
	return (cmd);
}
