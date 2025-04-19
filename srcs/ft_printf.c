/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:08:51 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 11:40:51 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, fmt);
	while (*fmt != '\0')
	{
		if (*fmt != '%')
		{
			ft_putchar_fd(*fmt++, 1);
			if (count >= 0)
				++count;
		}
		else
			fmt = parse(++fmt, &args, &count);
	}
	va_end(args);
	return (count);
}
