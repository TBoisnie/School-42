/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:17:21 by tboisnie          #+#    #+#             */
/*   Updated: 2020/08/25 19:42:03 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include "libft/string/string.h"
#include "libft/io/io.h"
#include "builtin/builtin.h"
#include "execute/execute.h"
#include "get_input/get_input.h"
#include "parser/parser.h"
#include "signal/signal.h"
#include "minishell.h"

volatile pid_t	g_running = 0;
volatile int	g_stop = 0;

void		show_prompt(void)
{
	io_put_str("\e[32m", IO_OUT);
	builtin_pwd(NULL, NULL);
	io_put_color("\u03BB ", IO_C_BLUE, IO_OUT);
}

static int	handle_prompt(char **line)
{
	int		gnl;

	show_prompt();
	if ((gnl = get_input(line)) <= 0)
	{
		if (gnl < 0)
		{
			io_put_err("MiniShell: get_next_line() failed.");
			return (1);
		}
		else if (!**line)
		{
			free(*line);
			io_put_endl("exit", IO_OUT);
			return (2);
		}
	}
	return (0);
}

static void	handle_command(char *line, t_env *env, int *exit_code)
{
	t_cmd	*cmd;
	int		error;

	if ((error = check_command(line, env)))
	{
		*exit_code = error;
		return ;
	}
	g_stop = 0;
	while (line && *line != '\0' && g_stop != 1)
	{
		if ((cmd = parser_parse(line, *env, *exit_code, &error)))
		{
			*exit_code = execute(cmd, env);
			cmd_delete(cmd);
			line = parser_get_next(line);
		}
		else
			break ;
	}
	g_stop = 0;
}

static void	loop(t_env *env)
{
	char	*line;
	int		exit_code;
	int		handler;

	exit_code = 0;
	while (1)
	{
		if ((handler = handle_prompt(&line)) == 1)
			continue ;
		else if (handler == 2)
			break ;
		handle_command(line, env, &exit_code);
		free(line);
	}
}

int			main(int argc, char *argv[], char *envp[])
{
	t_env	env;
	t_env	*p_env;

	(void)argc;
	(void)argv;
	if (signal(SIGINT, &signal_handler) == SIG_ERR ||
		signal(SIGQUIT, &signal_handler) == SIG_ERR)
	{
		io_put_err("MiniShell: signal() failed.");
		return (1);
	}
	io_put_color(
		"\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n" \
		"~  (\\___/)                          ~\n" \
		"~  (=^.^=)      MiniShell  (v1.0)   ~\n" \
		"~  (\")_(\")                          ~\n" \
		"~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n",
		IO_C_GREY, IO_OUT);
	env = env_copy(envp);
	p_env = &env;
	loop(p_env);
	env_clear(*p_env);
	return (0);
}
