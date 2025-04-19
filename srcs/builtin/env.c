/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 17:04:36 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:04:11 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft/io/io.h"
#include "builtin.h"

int	builtin_env(t_cmd *cmd, t_env *env)
{
	size_t	i;

	(void)cmd;
	if (env && *env)
	{
		i = 0;
		while ((*env)[i])
			io_put_endl((*env)[i++], IO_OUT);
	}
	return (0);
}
