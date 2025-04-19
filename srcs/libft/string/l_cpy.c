/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_cpy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:31:21 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 21:39:26 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

size_t	str_l_cpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	cpy_len;

	src_len = str_length(src);
	cpy_len = (src_len >= size) ? size - 1 : src_len;
	if (size != 0)
	{
		dst[cpy_len] = '\0';
		while (--cpy_len)
			dst[cpy_len] = src[cpy_len];
	}
	return (src_len);
}
