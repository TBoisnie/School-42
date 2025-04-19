/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:18:10 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:06:52 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/string/string.h"
#include "builtin.h"

static int	get_builtin_index(t_cmd *cmd)
{
	char	*names[8];
	size_t	i;

	if (!cmd || !cmd->name)
		return (-1);
	names[0] = "cd";
	names[1] = "echo";
	names[2] = "pwd";
	names[3] = "export";
	names[4] = "unset";
	names[5] = "env";
	names[6] = "exit";
	names[7] = NULL;
	i = 0;
	while (names[i])
	{
		if (!str_n_cmp(cmd->name, names[i], str_length(names[i]) + 1))
			return (i);
		i++;
	}
	return (-1);
}

int			is_builtin(t_cmd *cmd)
{
	return (get_builtin_index(cmd) != -1);
}

int			execute_builtin(t_cmd *cmd, t_env *env)
{
	int index;
	int	(*builtin_cmd[8])(t_cmd*, t_env*);

	if (!cmd || !cmd->name)
		return (1);
	builtin_cmd[0] = builtin_cd;
	builtin_cmd[1] = builtin_echo;
	builtin_cmd[2] = builtin_pwd;
	builtin_cmd[3] = builtin_export;
	builtin_cmd[4] = builtin_unset;
	builtin_cmd[5] = builtin_env;
	builtin_cmd[6] = builtin_exit;
	builtin_cmd[7] = NULL;
	if ((index = get_builtin_index(cmd)) != -1)
		return (builtin_cmd[index](cmd, env));
	return (1);
}
