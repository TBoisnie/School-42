/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:55:47 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/08 14:47:12 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char	*mapi;
	size_t	i;

	i = 0;
	if (!(mapi = (char *)malloc((ft_strlen(str) + 1) * sizeof(char))))
	{
		return (NULL);
	}
	while (str[i] != '\0')
	{
		mapi[i] = f(i, str[i]);
		++i;
	}
	mapi[i] = '\0';
	return (mapi);
}
