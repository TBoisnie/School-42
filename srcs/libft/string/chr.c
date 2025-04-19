/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:22:03 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:28:13 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "string.h"

char	*str_chr(const char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return ((char *)str);
		++str;
	}
	if (*str == c)
		return ((char *)str);
	return (NULL);
}
