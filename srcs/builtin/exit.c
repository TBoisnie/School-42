/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rqouchic <rqouchic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:27:18 by tboisnie          #+#    #+#             */
/*   Updated: 2020/10/15 16:37:03 by rqouchic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/string/string.h"
#include "builtin.h"

static int	check_error(t_cmd *cmd, int args_count)
{
	int	has_error;
	int i;
	int j;

	has_error = 0;
	i = 0;
	j = 1;
	if (args_count != 1)
	{
		if (cmd->args[j][i] == '-' || cmd->args[j][i] == '+')
			i++;
		while (cmd->args[j][i])
		{
			if (cmd->args[j][i] < '0' || cmd->args[j][i] > '9')
				break ;
			i++;
		}
		if (cmd->args[j][i] || (i == 1 && (cmd->args[j][i - 1] == '-'
			|| cmd->args[j][i - 1] == '+')))
			has_error = 2;
		else
			cmd->exit_code = str_atoi(cmd->args[1]);
	}
	return (has_error);
}

static int	check_numeric(t_cmd *cmd)
{
	int args_count;
	int	has_error;

	args_count = 0;
	while (cmd->args[args_count])
		args_count++;
	if (args_count > 2)
		has_error = 1;
	has_error = check_error(cmd, args_count);
	if (has_error)
	{
		cmd->exit_code = has_error;
		if (cmd->exit_code == 1)
			io_put_err("Builtin_exit: Too many arguments.");
		else
			io_put_err("Builtin_exit: Numeric argument required.");
	}
	return (has_error);
}

int			builtin_exit(t_cmd *cmd, t_env *env)
{
	int exit_code;
	int	had_error;

	had_error = check_numeric(cmd);
	exit_code = cmd->exit_code;
	if (!had_error || exit_code != 1)
	{
		cmd_delete(cmd);
		env_clear(*env);
		exit(exit_code);
	}
	return (exit_code);
}
