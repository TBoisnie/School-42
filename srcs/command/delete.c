/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 22:45:45 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:09:17 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "command.h"

t_cmd	*cmd_delete(t_cmd *cmd)
{
	size_t	i;

	if (!cmd)
		return (NULL);
	free(cmd->name);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
	}
	free(cmd->args);
	if (cmd->piped)
		cmd_delete(cmd->piped);
	free(cmd->file_in);
	free(cmd->file_out);
	free(cmd);
	return (NULL);
}
