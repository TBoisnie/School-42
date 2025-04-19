/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:43:04 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/05 01:43:12 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*mem_copy(void *mem_dest, const void *mem_src, size_t length)
{
	char		*str_dest;
	const char	*str_src;

	str_dest = mem_dest;
	str_src = mem_src;
	while (length-- > 0)
		*str_dest++ = *str_src++;
	return (str_dest);
}
