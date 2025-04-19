/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:31:51 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/05 09:43:46 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	s1_s2_len;
	int		i;

	i = 0;
	s1_s2_len = ft_strlen(s1) + ft_strlen(s2);
	if (!(join = (char *)malloc((s1_s2_len + 1) * sizeof(char))))
	{
		return (NULL);
	}
	while (*s1 != '\0')
	{
		join[i++] = *s1++;
	}
	while (*s2 != '\0')
	{
		join[i++] = *s2++;
	}
	join[i] = '\0';
	return (join);
}
