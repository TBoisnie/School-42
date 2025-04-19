/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:42:00 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:04:14 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io/io.h"
#include "libft/string/string.h"
#include "builtin.h"

static int	ignore_new_line(t_cmd *cmd)
{
	int		i;
	char	*cursor;

	i = 0;
	while (cmd->args[++i])
	{
		if (str_n_cmp(cmd->args[i], "-n", 2))
			break ;
		cursor = cmd->args[i];
		while (*++cursor != '\0')
			if (*cursor != 'n')
				break ;
		if (*cursor != '\0' && *cursor != 'n')
			break ;
	}
	return (i);
}

int			builtin_echo(t_cmd *cmd, t_env *env)
{
	size_t	i;
	int		new_line;

	(void)env;
	if (!cmd)
		return (1);
	if (cmd->args)
	{
		i = ignore_new_line(cmd);
		new_line = (i == 1);
		while (cmd->args[i])
		{
			io_put_str(cmd->args[i++], IO_OUT);
			if (cmd->args[i])
				io_put_str(" ", IO_OUT);
		}
		if (new_line)
			io_put_str("\n", IO_OUT);
	}
	return (0);
}
