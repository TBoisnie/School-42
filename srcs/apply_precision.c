/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 22:35:51 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 17:16:01 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static void	number_fill(t_placeholder *ph, char c)
{
	char	*tmp;
	int		len;
	int		is_neg;
	size_t	i;

	tmp = ph->str;
	len = (int)ft_strlen(ph->str);
	is_neg = (ph->value < 0);
	if (ph->precision > (len - is_neg))
	{
		if ((ph->str = malloc((ph->precision + 1) * sizeof(char))))
		{
			i = 0;
			if (is_neg)
				ph->str[i++] = '-';
			while (ph->precision-- > (len - is_neg))
				ph->str[i++] = c;
			ft_memcpy(&ph->str[i], &tmp[is_neg], len - is_neg + 1);
			free(tmp);
		}
		else
			ph->error = 1;
	}
}

void		apply_precision(t_placeholder *ph)
{
	char	*tmp;

	if (ph->type == 's' && ph->has_dot)
	{
		tmp = ph->str;
		if ((ph->str = ft_substr(tmp, 0, ph->precision)))
			free(tmp);
		else
			ph->error = 1;
	}
	else if (ft_strchr("pdiuxX", ph->type))
	{
		if (ph->has_dot && ph->precision > 0)
			number_fill(ph, '0');
		else if (ph->has_dot && ph->precision == 0 && ph->value == 0
			&& ph->uvalue == 0)
		{
			free(ph->str);
			if (!(ph->str = ft_calloc(1, sizeof(char))))
				ph->error = 1;
		}
	}
}
