/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_cmp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:39:34 by tboisnie          #+#    #+#             */
/*   Updated: 2020/08/25 18:49:37 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	str_n_cmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 && s2)
		return (0 - (unsigned char)*s2);
	if (s1 && !s2)
		return ((unsigned char)*s1);
	if (!s1 && !s2)
		return (0);
	while (n--)
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		if (*s1 == '\0' || *s2 == '\0')
			return (0);
		++s1;
		++s2;
	}
	return (0);
}
