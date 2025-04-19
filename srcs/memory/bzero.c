/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 06:39:04 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/26 08:19:27 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

void	*mem_bzero(void *mem, size_t length)
{
	unsigned char	*str_mem;

	str_mem = mem;
	while (length-- > 0)
		str_mem[length] = 0;
	return (mem);
}
