/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 07:02:51 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 07:03:01 by tboisnie         ###   ########.fr       */
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
