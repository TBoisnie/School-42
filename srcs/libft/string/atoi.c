/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:44:30 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 20:53:56 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../char/char.h"
#include "string.h"

int	str_atoi(const char *str)
{
	long	n;
	int		sign;
	size_t	i;

	n = 0;
	sign = 1;
	i = 0;
	while (char_is_space(str[i]))
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
