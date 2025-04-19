/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 17:23:32 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:13:49 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/string/string.h"
#include "env.h"

char	*env_get(t_env env, char *key)
{
	char	*equal;

	while (env && *env)
	{
		equal = str_chr(*env, '=');
		*equal = '\0';
		if (!str_n_cmp(*env, key, str_length(key) + 1))
		{
			*equal = '=';
			return (equal + 1);
		}
		*equal = '=';
		env++;
	}
	return (NULL);
}
