/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 22:57:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:09:37 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/io.h"
#include "libft/array/array.h"
#include "command.h"

t_cmd	*cmd_arg_add(t_cmd *cmd, char *arg)
{
	char	**args_old;

	if (cmd && arg)
	{
		args_old = cmd->args;
		cmd->args = arr_str_append(cmd->args, arg);
		if (cmd->args == args_old)
		{
			io_put_err("Cmd_arg_add: arr_str_append() failed.");
			return (NULL);
		}
	}
	return (cmd);
}
