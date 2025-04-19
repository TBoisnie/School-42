/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_cat.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:29:13 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 20:37:44 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

size_t	str_l_cat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	dst_len = str_length(dst);
	dst_len = (size < dst_len) ? size : dst_len;
	src_len = str_length(src);
	if (size != 0 && dst_len < size)
	{
		while (*dst != '\0')
			++dst;
		while (*src != '\0' && (size - dst_len - 1) > 0)
		{
			*dst++ = *src++;
			--size;
		}
		*dst = '\0';
	}
	return (dst_len + src_len);
}
