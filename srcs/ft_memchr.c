/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:50:40 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/05 06:25:48 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t n)
{
	const unsigned char	*s;

	s = (const unsigned char *)b;
	while (n--)
	{
		if (*s == (unsigned char)c)
		{
			return ((void *)s);
		}
		++s;
	}
	return (NULL);
}
