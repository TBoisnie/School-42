/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:53:09 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:16:38 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*mem_move(void *mem_dst, const void *mem_src, size_t length)
{
	char		*str_dst;
	const char	*str_src;

	str_dst = (char *)mem_dst;
	str_src = (const char *)mem_src;
	if (str_dst > str_src)
	{
		while (length--)
			str_dst[length] = str_src[length];
	}
	else
	{
		while (length--)
			*str_dst++ = *str_src++;
	}
	return (mem_dst);
}
