/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:02:23 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:16:58 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

int	mem_cmp(const void *mem_a, const void *mem_b, size_t length)
{
	const unsigned char	*str_a;
	const unsigned char	*str_b;

	str_a = (const unsigned char *)mem_a;
	str_b = (const unsigned char *)mem_b;
	while (length--)
	{
		if (*str_a != *str_b)
			return (*str_a - *str_b);
		++str_a;
		++str_b;
	}
	return (0);
}
