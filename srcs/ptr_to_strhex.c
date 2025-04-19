/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_to_strhex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:09:55 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 05:56:11 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "ft_printf.h"

static size_t	hex_len(uintptr_t n)
{
	size_t	len;

	len = 1;
	while ((n /= 16) > 0)
		++len;
	return (len);
}

char			*ptr_to_strhex(uintptr_t ptr)
{
	char	*str;
	size_t	len;

	len = hex_len(ptr);
	if ((str = (char *)malloc((len + 1) * sizeof(char))))
	{
		str[len] = '\0';
		if (ptr == 0)
			*str = '0';
		while (len > 0)
		{
			str[len - 1] = (ptr % 16 <= 9) ?
				'0' + (ptr % 16) :
				'a' + (ptr % 16 - 10);
			ptr /= 16;
			--len;
		}
	}
	return (str);
}
