/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:25:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/02 18:16:15 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "libft/io/io.h"
#include "libft/system/system.h"
#include "parser/parser.h"
#include "builtin/builtin.h"
#include "separator/separator.h"
#include "execute.h"

extern pid_t	g_running;

static void		handle_child(t_cmd *cmd, int pipe_fd_old[2],
	int pipe_fd_new[2], t_bool first)
{
	if (!first)
	{
		if (dup2(pipe_fd_old[0], IO_IN) == -1)
			sys_exit(EXIT_ERROR, "Execute_pipe: dup2(1) failed.");
		close(pipe_fd_old[0]);
		close(pipe_fd_old[1]);
	}
	if (cmd->piped)
	{
		close(pipe_fd_new[0]);
		if (dup2(pipe_fd_new[1], IO_OUT) == -1)
			sys_exit(EXIT_ERROR, "Execute_pipe: dup2(2) failed.");
		close(pipe_fd_new[1]);
	}
	if (cmd->file_in && (cmd->exit_code = redirect_in(cmd)))
		exit(cmd->exit_code);
	if (cmd->file_out && (cmd->exit_code = redirect_out(cmd, 1)))
		exit(cmd->exit_code);
}

static void		launch(t_cmd *cmd, t_env env)
{
	if (!cmd->executable)
		sys_exit(127, "Execute_pipe: Command not found.");
	else if (is_builtin(cmd))
		exit(execute_builtin(cmd, &env));
	else if (cmd->name)
	{
		execve(cmd->name, cmd->args, env);
		sys_exit(126, "Execute_pipe: execve() failed.");
	}
	exit(0);
}

static void		handle_parent(t_cmd *cmd, int pipe_fd_old[2],
	int pipe_fd_new[2], t_bool first)
{
	if (!first)
	{
		close(pipe_fd_old[0]);
		close(pipe_fd_old[1]);
	}
	if (cmd->piped)
	{
		pipe_fd_old[0] = pipe_fd_new[0];
		pipe_fd_old[1] = pipe_fd_new[1];
	}
}

static int		wait_all(int cmd_count)
{
	int		exit_code;
	int		w_pid;
	int		tmp_exit_code;

	while (cmd_count--)
	{
		w_pid = waitpid(-1, &tmp_exit_code, 0);
		if (w_pid == 0 || g_running == 0 || w_pid == g_running)
			exit_code = tmp_exit_code;
	}
	if (WIFEXITED(exit_code))
		exit_code = WEXITSTATUS(exit_code);
	else if (WIFSIGNALED(exit_code))
		exit_code = WTERMSIG(exit_code) + 128;
	else if (WIFSTOPPED(exit_code))
		exit_code = WSTOPSIG(exit_code);
	g_running = 0;
	return (exit_code);
}

int				execute_pipe(t_cmd *cmd, t_env env)
{
	int		pipe_fd_old[2];
	int		pipe_fd_new[2];
	t_bool	first;
	int		cmd_count;

	first = TRUE;
	cmd_count = 0;
	while (cmd)
	{
		if (cmd->piped && pipe(pipe_fd_new) == -1)
			sys_exit(EXIT_ERROR, "Execute_pipe: pipe() failed.");
		if ((g_running = fork()) == -1)
			sys_exit(EXIT_ERROR, "Execute_pipe: fork() failed.");
		else if (g_running == 0)
		{
			handle_child(cmd, pipe_fd_old, pipe_fd_new, first);
			cmd = check_execute(cmd, env);
			launch(cmd, env);
		}
		handle_parent(cmd, pipe_fd_old, pipe_fd_new, first);
		cmd_count += 1;
		first = FALSE;
		cmd = cmd->piped;
	}
	return (wait_all(cmd_count));
}
