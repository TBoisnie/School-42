/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_cpy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:06:10 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:17:04 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*mem_c_cpy(void *dst, const void *src, int c, size_t n)
{
	char		*sdst;
	const char	*ssrc;

	sdst = (char *)dst;
	ssrc = (const char *)src;
	while (n--)
	{
		*sdst++ = *ssrc;
		if (*ssrc++ == (char)c)
			return ((void *)sdst);
	}
	return (NULL);
}
