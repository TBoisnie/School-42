/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_chr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:33:06 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 21:34:04 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_r_chr(const char *str, int c)
{
	char	*last;

	last = NULL;
	while (*str != '\0')
	{
		if (*str == (char)c)
			last = (char *)str;
		++str;
	}
	if (*str == (char)c)
		last = (char *)str;
	return (last);
}
