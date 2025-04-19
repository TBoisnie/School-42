/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:58:16 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 01:53:52 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

const char	*check_precision(const char *fmt, t_placeholder *ph, va_list *args)
{
	ph->precision = 0;
	ph->has_dot = '\0';
	if (*fmt != '.')
		return (fmt);
	++fmt;
	ph->has_dot = '.';
	if (*fmt == '*')
	{
		ph->precision = (int)va_arg(*args, int);
		if (ph->precision < 0)
			ph->has_dot = '\0';
		++fmt;
	}
	else
	{
		while ('0' <= *fmt && *fmt <= '9')
		{
			ph->precision *= 10;
			ph->precision += (*fmt - '0');
			++fmt;
		}
	}
	return (fmt);
}
