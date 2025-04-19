/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:09:55 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 12:01:22 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

#include <stdio.h>

static int		ll_len(long long n, int base_size)
{
	int	len;

	len = 1;
	while ((n /= base_size) != 0)
		++len;
	return (len);
}

char			*ft_lltoa_base(long long n, char *base)
{
	char		*str;
	int			len;
	int			base_size;
	int			is_neg;
	int			digit;

	is_neg = (n < 0);
	base_size = (int)ft_strlen(base);
	len = ll_len(n, base_size) + is_neg;
	if ((str = malloc((len + 1) * sizeof(char))))
	{
		if (is_neg)
			str[0] = '-';
		else if (n == 0)
			str[0] = '0';
		str[len--] = '\0';
		while (n != 0)
		{
			digit = n % base_size;
			str[len--] = base[digit < 0 ? -digit : digit];
			n /= base_size;
		}
	}
	return (str);
}
