/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:17:52 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 13:39:17 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	str_fill(t_placeholder *ph, char c, size_t len, int *count)
{
	while ((ph->width - (int)len) > 0)
	{
		ft_putchar_fd(c, 1);
		ph->width--;
		if (!ph->error)
			++*count;
	}
}

static void	apply_width_next(t_placeholder *ph, size_t len, int *count)
{
	if (has_flag('0', ph))
	{
		if (ph->value < 0)
		{
			ft_putchar_fd('-', 1);
			ph->offset = 1;
		}
		else if (has_flag('+', ph) || has_flag(' ', ph))
		{
			ft_putchar_fd(has_flag('+', ph) ? '+' : ' ', 1);
			ph->offset = 1;
		}
		else if (has_flag('#', ph) && ft_strchr("pxX", ph->type))
		{
			ft_putstr_fd((ph->type == 'X') ? "0X" : "0x", 1);
			ph->offset = 2;
		}
		str_fill(ph, '0', len, count);
	}
	else
		str_fill(ph, ' ', len, count);
}

void		apply_width(t_placeholder *ph, size_t len, int append, int *count)
{
	ph->offset = 0;
	if (has_flag('-', ph) && append)
		str_fill(ph, ' ', len, count);
	else if (!has_flag('-', ph) && !append)
		apply_width_next(ph, len, count);
}
