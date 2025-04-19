/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 09:44:04 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/14 20:10:07 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trimmed_char(char const c, char const *set)
{
	if (set != NULL)
	{
		while (*set != '\0')
		{
			if (c == *set++)
				return (1);
		}
	}
	return (0);
}

char		*ft_strtrim(char const *str, char const *set)
{
	const char	*end;

	if (str == NULL)
		return (NULL);
	end = str + ft_strlen(str) - 1;
	while (*str != '\0' && is_trimmed_char(*str, set))
		++str;
	while (end >= str && is_trimmed_char(*end, set))
		--end;
	return (ft_substr(str, 0, end + 1 - str));
}
