/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 19:20:24 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:12:28 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/types.h"
#include "libft/string/string.h"
#include "env.h"

static void	move_following(t_bool done, t_env env, size_t i)
{
	while (done)
	{
		env[i - 1] = env[i];
		if (!env[i++])
			break ;
	}
}

t_env		env_delete(t_env env, char *key)
{
	size_t	i;
	char	*env_k;
	char	*env_v;
	t_bool	done;

	if (!env)
		return (NULL);
	done = FALSE;
	i = 0;
	while (env[i] && !done)
	{
		env_k = env[i];
		env_v = str_chr(env[i], '=');
		*env_v++ = '\0';
		if (!str_n_cmp(env_k, key, str_length(key) + 1))
		{
			free(env[i]);
			done = TRUE;
		}
		else
			*--env_v = '=';
		i++;
	}
	move_following(done, env, i);
	return (env);
}
