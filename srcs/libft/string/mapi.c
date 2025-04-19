/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:59:25 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 20:59:56 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "string.h"

char	*str_mapi(char const *str, char (*f)(unsigned int, char))
{
	char	*mapi;
	size_t	i;

	i = 0;
	if (!(mapi = malloc((str_length(str) + 1) * sizeof(char))))
		return (NULL);
	while (str[i] != '\0')
	{
		mapi[i] = f(i, str[i]);
		++i;
	}
	mapi[i] = '\0';
	return (mapi);
}
