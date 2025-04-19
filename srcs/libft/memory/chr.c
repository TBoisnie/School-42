/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:07:30 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:17:25 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*mem_chr(const void *mem, int c, size_t length)
{
	const unsigned char	*str;

	str = (const unsigned char *)mem;
	while (length--)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		++str;
	}
	return (NULL);
}
