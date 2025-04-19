/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:25:21 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/02 22:15:17 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_command(char *line, t_env *env)
{
	t_cmd	*tmp_cmd;
	int		error;

	error = 0;
	while (line && *line != '\0')
	{
		if ((tmp_cmd = parser_parse(line, *env, 0, &error)))
		{
			cmd_delete(tmp_cmd);
			line = parser_get_next(line);
		}
		else
			break ;
	}
	return (error);
}
