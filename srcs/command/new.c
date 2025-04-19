/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 22:22:58 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:09:04 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "command.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	if (!(cmd = malloc(sizeof(t_cmd))))
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->piped = NULL;
	cmd->append = FALSE;
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	cmd->executable = TRUE;
	cmd->exit_code = 0;
	return (cmd);
}
