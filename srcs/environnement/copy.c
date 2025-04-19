/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 15:56:16 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:11:51 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/string/string.h"
#include "libft/array/array.h"
#include "env.h"

t_env	env_copy(char *envp[])
{
	t_env	env;
	size_t	size;
	size_t	i;

	if (!(size = arr_str_length(envp)))
		return (NULL);
	if (!(env = arr_str_new(size)))
	{
		io_put_err("Env_copy: arr_str_new() failed.");
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		if (!(env[i] = str_dup(envp[i])))
			break ;
		i++;
	}
	if (i != size)
	{
		env_clear(env);
		io_put_err("Env_copy: str_dup() failed.");
		return (NULL);
	}
	return (env);
}
