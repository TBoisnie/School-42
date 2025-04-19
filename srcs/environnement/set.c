/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 16:26:34 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:13:34 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/array/array.h"
#include "libft/string/string.h"
#include "env.h"

static int	try_replace(t_env env, char *str)
{
	char	*equal;
	char	end;
	size_t	i;

	equal = str_chr(str, '=');
	end = *++equal;
	*equal = '\0';
	i = 0;
	while (env && env[i])
	{
		if (!str_n_cmp(env[i], str, str_length(str)))
		{
			*equal = end;
			free(env[i]);
			env[i] = str;
			return (0);
		}
		i++;
	}
	*equal = end;
	return (1);
}

static void	populate(t_env env_old, t_env env_new, char *str)
{
	size_t	i;

	i = 0;
	while (env_old && env_old[i])
	{
		env_new[i] = env_old[i];
		env_old[i] = NULL;
		i++;
	}
	env_new[i] = str;
	free(env_old);
}

t_env		env_set(t_env env, char *var)
{
	char	*str;
	t_env	env_new;

	if (!(str = str_dup(var)))
	{
		io_put_err("Env_set: str_dup() failed.");
		return (env);
	}
	if (!try_replace(env, str))
		return (env);
	if (!(env_new = arr_str_new(arr_str_length(env) + 1)))
	{
		io_put_err("Env_set: arr_str_new() failed.");
		free(str);
		return (env);
	}
	populate(env, env_new, str);
	return (env_new);
}
