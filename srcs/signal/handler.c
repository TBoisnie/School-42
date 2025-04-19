/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 21:55:37 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/02 18:53:19 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include "libft/io/io.h"
#include "minishell.h"
#include "signal.h"

extern pid_t	g_running;
extern int		g_stop;

void	signal_handler(int code)
{
	if (code == SIGQUIT)
	{
		g_stop = 2;
		if (g_running > 0)
		{
			io_put_endl("Quit", IO_OUT);
			g_running = kill(g_running, SIGQUIT);
		}
	}
	else if (code == SIGINT)
	{
		g_stop = 1;
		io_put_endl("", IO_OUT);
		if (g_running > 0)
			g_running = kill(g_running, SIGINT);
		else if (g_running <= 0)
			show_prompt();
	}
}
