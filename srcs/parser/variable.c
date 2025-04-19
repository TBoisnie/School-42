/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 00:48:00 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/02 23:54:41 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/string/string.h"
#include "libft/char/char.h"
#include "parser.h"

static char	*handle_question(char **cursor, char *end, int exit_code,
	int *is_question)
{
	char	*str;

	*end = *(++(*cursor));
	*is_question = 1;
	if (!(str = str_itoa(exit_code)))
		io_put_err("Parser_variable: str_itoa() failed.");
	return (str);
}

static char	*handle_var(char **cursor, char *end, t_env env, t_state *st)
{
	char	*var_name;

	var_name = *cursor;
	if (*(*cursor - 1) == '~')
	{
		*end = **cursor;
		return (env_get(env, "HOME"));
	}
	while (char_is_alnum(**cursor) || **cursor == '_')
		(*cursor)++;
	*end = **cursor;
	if (var_name == *cursor && (st->in_quote || (*end != '\'' && *end != '\"')))
		--var_name;
	else if (var_name != *cursor)
	{
		**cursor = '\0';
		var_name = env_get(env, var_name);
	}
	**cursor = '\0';
	return (var_name);
}

static void	clean(t_state *st, char *tmp, char *str, int is_question)
{
	if (st->word != tmp)
		free(tmp);
	if (is_question)
		free(str);
}

void		append_to_word(t_state *st, char *str, char *tmp)
{
	char	*append;

	if (str_length(str) > 0)
	{
		append = str;
		if (!st->in_quote && !(append = remove_mult_space(str)))
		{
			st->error_code = 1;
			return ;
		}
		if (!(st->word = str_join(tmp, append)))
		{
			io_put_err("Parser_variable: str_join() failed.");
			st->error_code = 1;
		}
		if (append != str)
			free(append);
	}
}

char		*parser_variable(t_state *st, char *cursor, t_env env,
	int exit_code)
{
	char	*str;
	char	*tmp;
	char	end;
	int		is_question;

	++cursor;
	is_question = 0;
	if (*cursor == '?')
	{
		if (!(str = handle_question(&cursor, &end, exit_code, &is_question)))
			return ((st->error_code = 1) ? NULL : NULL);
	}
	else
		str = handle_var(&cursor, &end, env, st);
	tmp = st->word;
	append_to_word(st, str, tmp);
	*cursor = end;
	clean(st, tmp, str, is_question);
	return ((st->error_code) ? NULL : cursor);
}
