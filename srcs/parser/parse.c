/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 19:18:00 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/03 17:00:05 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/char/char.h"
#include "libft/string/string.h"
#include "parser.h"

static t_cmd	*do_init(t_state *st, int prev_exit_code)
{
	t_cmd	*first;

	if (!(first = cmd_new()))
	{
		io_put_err("Parser_parse: cmd_new() failed.");
		st->error_code = 1;
		return (NULL);
	}
	first->exit_code = prev_exit_code;
	parser_state_init(st);
	return (first);
}

static char		*do_parsing(char *str, t_state *st, t_env env,
	int prev_exit_code)
{
	if (*str == '>')
		str = parser_redirect_out(st, str);
	else if (*str == '<')
		str = parser_redirect_in(st, str);
	else if (*str == '$' || (*str == '~' && (str_chr(" \t", *(str + 1)) ||
		*(str + 1) == '\0')))
		str = parser_variable(st, str, env, prev_exit_code);
	else if (*str == '\\')
		str = parser_backslash(st, str);
	else if (*str == '\"')
		str = parser_d_quote(st, str, env, prev_exit_code);
	else if (*str == '\'')
		str = parser_s_quote(st, str);
	else
		str = parser_default(st, str);
	return (str);
}

static t_cmd	*check_clean(char *str, t_cmd *first, t_cmd *cmd, t_state *st)
{
	if (!str || !cmd || !cmd_is_valid(cmd) || !parser_state_is_clean(st))
	{
		if (st->file_in > 1 || st->file_out > 1)
			;
		else if (st->file_in || st->file_out)
		{
			io_put_err("Parser_parse: Invalid redirection file.");
			st->error_code = 2;
		}
		else if (cmd && !cmd_is_valid(cmd) && !st->error_code)
		{
			io_put_err("Parser_check_clean: Invalid command.");
			st->error_code = 2;
		}
		first = cmd_delete(first);
		free(st->word);
	}
	return (first);
}

static int		do_parsing_1(char **p_str, t_cmd **p_cmd, t_state *st)
{
	if (char_is_space(**p_str))
		*p_str = *p_str + 1;
	else
	{
		if (!cmd_is_valid(*p_cmd))
			return (1);
		*p_str = parser_pipe(*p_cmd, st, *p_str);
		*p_cmd = (*p_cmd)->piped;
	}
	return (0);
}

t_cmd			*parser_parse(char *str, t_env env, int prev_exit_code,
	int *error)
{
	t_state	st;
	t_cmd	*first;
	t_cmd	*cmd;

	if (!(first = do_init(&st, prev_exit_code)))
		return (NULL);
	cmd = first;
	while (str)
	{
		if (char_is_space(*str) || str_chr("|><;", *str) || *str == '\0')
			if (!(cmd = parser_save_word(cmd, &st)))
				break ;
		if (*str == '\0' || *str == ';')
			break ;
		else if (char_is_space(*str) || *str == '|')
		{
			if (do_parsing_1(&str, &cmd, &st))
				break ;
		}
		else
			str = do_parsing(str, &st, env, prev_exit_code);
	}
	cmd = check_clean(str, first, cmd, &st);
	*error = st.error_code;
	return (cmd);
}
