/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:36:19 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/08 18:03:24 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	dst_len = (size < dst_len) ? size : dst_len;
	src_len = ft_strlen(src);
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
