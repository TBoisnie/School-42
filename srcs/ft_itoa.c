/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:54:05 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/08 13:52:02 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	int_len(long safe_n)
{
	size_t	len;

	len = 0;
	if (safe_n == 0)
	{
		++len;
	}
	else if (safe_n < 0)
	{
		safe_n *= -1;
		++len;
	}
	while (safe_n > 0)
	{
		safe_n /= 10;
		++len;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	long	safe_n;

	safe_n = (long)n;
	i = int_len(safe_n);
	if (!(str = (char *)malloc((i + 1) * sizeof(char))))
	{
		return (NULL);
	}
	str[i] = '\0';
	if (safe_n == 0)
		str[0] = '0';
	else if (safe_n < 0)
	{
		str[0] = '-';
		safe_n *= -1;
	}
	while (safe_n > 0)
	{
		str[--i] = '0' + (safe_n % 10);
		safe_n /= 10;
	}
	return (str);
}
