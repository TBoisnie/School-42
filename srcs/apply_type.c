/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:26:45 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 11:53:18 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static void	apply_length_uxx(t_placeholder *ph, va_list *args)
{
	if (ph->length == 'H')
		ph->uvalue = (unsigned char)va_arg(*args, int);
	else if (ph->length == 'h')
		ph->uvalue = (unsigned short)va_arg(*args, int);
	else if (ph->length == 'L')
		ph->uvalue = (unsigned long long)va_arg(*args, unsigned long long);
	else if (ph->length == 'l')
		ph->uvalue = (unsigned long)va_arg(*args, unsigned long);
	else
		ph->uvalue = (unsigned int)va_arg(*args, unsigned int);
	if (ph->type == 'u')
		ph->str = ft_ulltoa_base(ph->uvalue, "0123456789");
	else if (ph->type == 'X')
		ph->str = ft_ulltoa_base(ph->uvalue, "0123456789ABCDEF");
	else
		ph->str = ft_ulltoa_base(ph->uvalue, "0123456789abcdef");
}

static void	apply_length_di(t_placeholder *ph, va_list *args)
{
	if (ph->length == 'H')
		ph->value = (signed char)va_arg(*args, int);
	else if (ph->length == 'h')
		ph->value = (short)va_arg(*args, int);
	else if (ph->length == 'L')
		ph->value = (long long)va_arg(*args, long long);
	else if (ph->length == 'l')
		ph->value = (long)va_arg(*args, long);
	else
		ph->value = (int)va_arg(*args, int);
	ph->str = ft_lltoa_base((long long)ph->value, "0123456789");
}

static void	apply_type_next(t_placeholder *ph, va_list *args)
{
	if (ph->type == 'c')
		ph->str = int_to_struchar((unsigned char)va_arg(*args, int));
	else if (ph->type == 's')
	{
		ph->str = (char *)va_arg(*args, char *);
		if (ph->str == NULL)
			ph->str = ft_strdup("(null)");
		else
			ph->str = ft_strdup(ph->str);
	}
	else if (ph->type == 'p')
		ph->str = ptr_to_strhex((uintptr_t)va_arg(*args, uintptr_t));
}

void		apply_type(t_placeholder *ph, va_list *args)
{
	ph->str = NULL;
	ph->value = 0;
	ph->uvalue = 0;
	if (ph->type == '%')
		ph->str = ft_strdup("%");
	else if (ph->type == 'd' || ph->type == 'i')
	{
		apply_length_di(ph, args);
		if (ph->has_dot)
			remove_flag('0', ph);
	}
	else if (ft_strchr("uxX", ph->type))
	{
		apply_length_uxx(ph, args);
		if (ph->uvalue == 0)
			remove_flag('#', ph);
	}
	else
		apply_type_next(ph, args);
	if (!ph->str)
		ph->error = 1;
}
