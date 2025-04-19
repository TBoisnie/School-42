/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:59:25 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/10 22:17:47 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*mem_set(void *mem, int c, size_t length)
{
	unsigned char	*str;

	str = (unsigned char *)mem;
	while (length--)
		*str++ = (unsigned char)c;
	return (mem);
}
