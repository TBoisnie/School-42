/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:23:09 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 21:40:41 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*str_trim(char const *str, char const *set)
{
	const char	*end;

	if (str == NULL)
		return (NULL);
	end = str + str_length(str) - 1;
	while (*str != '\0' && str_chr(set, *str))
		++str;
	while (end >= str && str_chr(set, *end))
		--end;
	return (str_sub(str, 0, end + 1 - str));
}
