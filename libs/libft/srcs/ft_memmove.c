/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:29:59 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/14 19:48:11 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*sdst;
	const char	*ssrc;

	sdst = (char *)dst;
	ssrc = (const char *)src;
	if (sdst > ssrc)
	{
		while (n--)
		{
			sdst[n] = ssrc[n];
		}
	}
	else
	{
		while (n--)
		{
			*sdst++ = *ssrc++;
		}
	}
	return (dst);
}
