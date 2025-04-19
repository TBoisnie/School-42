/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:29:55 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 01:56:03 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

const char	*check_width(const char *fmt, t_placeholder *ph, va_list *args)
{
	ph->width = 0;
	if (*fmt == '*')
	{
		if ((ph->width = (int)va_arg(*args, int)) < 0)
		{
			add_flag('-', ph);
			ph->width *= -1;
		}
		++fmt;
	}
	else
	{
		while ('0' <= *fmt && *fmt <= '9')
		{
			ph->width *= 10;
			ph->width += (*fmt - '0');
			++fmt;
		}
	}
	return (fmt);
}
