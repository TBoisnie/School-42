/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:09:55 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 11:52:05 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static int		ull_len(unsigned long long n, int base_size)
{
	int	len;

	len = 1;
	while ((n /= base_size) != 0)
		++len;
	return (len);
}

char			*ft_ulltoa_base(unsigned long long n, char *base)
{
	char	*str;
	int		len;
	int		base_size;

	base_size = ft_strlen(base);
	len = ull_len(n, base_size);
	if ((str = malloc((len + 1) * sizeof(char))))
	{
		if (n == 0)
			str[0] = '0';
		str[len--] = '\0';
		while (n != 0)
		{
			str[len--] = base[n % base_size];
			n /= base_size;
		}
	}
	return (str);
}
