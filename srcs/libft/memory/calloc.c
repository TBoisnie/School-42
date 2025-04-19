/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:23:12 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 21:24:40 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "memory.h"

void	*mem_calloc(size_t length, size_t size)
{
	void	*mem;

	if ((mem = malloc(length * size)))
		mem_bzero(mem, length * size);
	return (mem);
}
