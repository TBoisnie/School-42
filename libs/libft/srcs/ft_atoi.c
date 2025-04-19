/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:41:44 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/11 00:19:15 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int			ft_atoi(const char *str)
{
	long	n;
	int		sign;
	size_t	i;

	n = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
	{
		++i;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		++i;
	}
	return ((int)(sign * n));
}
