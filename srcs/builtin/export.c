/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:52:34 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:06:24 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/types.h"
#include "libft/io/io.h"
#include "libft/char/char.h"
#include "libft/array/array.h"
#include "libft/string/string.h"
#include "builtin.h"

t_bool			is_valid_name(char *str)
{
	if (!str || !*str || char_is_digit(*str))
		return (FALSE);
	while (*str)
	{
		if (!char_is_alnum(*str) && *str != '_')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void		process_unique(t_cmd *cmd, t_env *env, int *error, int i)
{
	char	*equal;

	if ((equal = str_chr(cmd->args[i], '=')))
	{
		*equal = '\0';
		if (!is_valid_name(cmd->args[i]))
		{
			*equal = '=';
			io_put_err("Builtin_export: Invalid variable name.");
			*error = 1;
		}
		else
		{
			*equal = '=';
			*env = env_set(*env, cmd->args[i]);
		}
	}
	else if (!is_valid_name(cmd->args[i]))
	{
		io_put_err("Builtin_export: Invalid variable name.");
		*error = 1;
	}
}

static int		process(t_cmd *cmd, t_env *env)
{
	size_t	i;
	int		error;

	error = 0;
	i = 0;
	while (cmd->args[++i])
		process_unique(cmd, env, &error, i);
	return (error);
}

int				print_sorted_env(t_env env)
{
	char	**copy;
	char	*equal;
	int		i;

	copy = arr_str_copy(env);
	if (!copy)
	{
		io_put_err("Builtin_export: Env copy failed.");
		return (1);
	}
	arr_str_sort(copy, str_cmp);
	i = -1;
	while (copy[++i])
	{
		equal = str_chr(copy[i], '=');
		io_put_str("declare -x ", IO_OUT);
		*equal = '\0';
		io_put_str(copy[i], IO_OUT);
		*equal = '=';
		io_put_str("=\"", IO_OUT);
		io_put_str(++equal, IO_OUT);
		io_put_endl("\"", IO_OUT);
	}
	arr_str_clear(copy);
	return (0);
}

int				builtin_export(t_cmd *cmd, t_env *env)
{
	if (!env)
	{
		io_put_err("Builtin_export: Invalid environnement pointer.");
		return (1);
	}
	if (arr_str_length(cmd->args) <= 1)
	{
		return (print_sorted_env(*env));
	}
	return (process(cmd, env));
}
