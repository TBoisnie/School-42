/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 15:40:21 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:11:41 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env.h"

t_env	env_clear(t_env env)
{
	size_t	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (NULL);
}
