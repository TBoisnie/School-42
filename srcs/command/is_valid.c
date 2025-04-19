/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 20:30:57 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:09:11 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/types.h"
#include "command.h"

t_bool	cmd_is_valid(t_cmd *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!cmd->name && !cmd->file_in && !cmd->file_out)
		return (FALSE);
	return (TRUE);
}
