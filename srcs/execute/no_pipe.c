/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:08:48 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/02 18:37:27 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/io/io.h"
#include "builtin/builtin.h"
#include "separator/separator.h"
#include "execute.h"

static int	save_fd(t_cmd *cmd, int *save_fd_in, int *save_fd_out)
{
	int	exit_code;

	exit_code = 0;
	if (cmd->file_in)
	{
		*save_fd_in = dup(IO_IN);
		if ((exit_code = redirect_in(cmd)))
			return (exit_code);
	}
	if (cmd->file_out)
	{
		*save_fd_out = dup(IO_OUT);
		if ((exit_code = redirect_out(cmd, 1)))
			return (exit_code);
	}
	return (exit_code);
}

static void	restore_fd(t_cmd *cmd, int *save_fd_in, int *save_fd_out)
{
	if (cmd->file_in)
	{
		dup2(*save_fd_in, IO_IN);
		close(*save_fd_in);
	}
	if (cmd->file_out)
	{
		dup2(*save_fd_out, IO_OUT);
		close(*save_fd_out);
	}
}

int			execute_no_pipe(t_cmd *cmd, t_env *env)
{
	int		save_fd_in;
	int		save_fd_out;
	int		exit_code;

	if ((exit_code = save_fd(cmd, &save_fd_in, &save_fd_out)))
		return (exit_code);
	exit_code = execute_builtin(cmd, env);
	restore_fd(cmd, &save_fd_in, &save_fd_out);
	return (exit_code);
}
