/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:04:44 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/05 06:41:20 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	cpy_len;

	src_len = ft_strlen(src);
	cpy_len = (src_len >= size) ? size - 1 : src_len;
	if (size != 0)
	{
		ft_memcpy(dst, src, cpy_len);
		dst[cpy_len] = '\0';
	}
	return (src_len);
}
