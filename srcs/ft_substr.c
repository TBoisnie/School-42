/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:12:07 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/05 16:22:22 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	str_len;

	str_len = ft_strlen(str);
	if (start >= str_len)
		len = 0;
	else if (start + len > str_len)
		len = str_len - start;
	if (!(sub = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len && str[start + i] != '\0')
	{
		sub[i] = str[start + i];
		++i;
	}
	sub[i] = '\0';
	return (sub);
}
