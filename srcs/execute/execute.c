/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:32:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/02 16:42:59 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "builtin/builtin.h"
#include "execute.h"

int	execute(t_cmd *cmd, t_env *env)
{
	if (cmd->piped || !is_builtin(cmd))
		return (execute_pipe(cmd, env ? *env : NULL));
	else
		return (execute_no_pipe(cmd, env));
}
