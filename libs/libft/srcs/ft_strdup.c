/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 07:39:11 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/05 07:57:18 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	str_size;

	str_size = (ft_strlen(str) + 1) * sizeof(char);
	if (!(dup = (char *)malloc(str_size)))
	{
		return (NULL);
	}
	ft_memcpy(dup, str, str_size);
	return (dup);
}
