/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:55:25 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:03:39 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "builtin.h"

int	builtin_unset(t_cmd *cmd, t_env *env)
{
	size_t	i;
	int		code;

	code = 0;
	if (!cmd->args || !env)
		return (code);
	i = 0;
	while (cmd->args[++i])
	{
		if (is_valid_name(cmd->args[i]))
			env_delete(*env, cmd->args[i]);
		else
		{
			io_put_err("Builtin_export: Invalid variable name.");
			code = 1;
		}
	}
	return (code);
}
