/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:07:08 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/05 06:17:13 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char		*sdst;
	const char	*ssrc;

	sdst = (char *)dst;
	ssrc = (const char *)src;
	while (n--)
	{
		*sdst++ = *ssrc;
		if (*ssrc++ == (char)c)
		{
			return ((void *)sdst);
		}
	}
	return (NULL);
}
