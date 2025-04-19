/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:09:21 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 14:24:10 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

static void			apply_placeholder(va_list *args, int *count,
	t_placeholder *ph)
{
	size_t len;

	apply_type(ph, args);
	if (ph->error)
		return ;
	apply_precision(ph);
	if (ph->error)
		return ;
	apply_flags(ph);
	if (ph->error)
		return ;
	len = (ph->type == 'c') ? 1 : ft_strlen(ph->str);
	*count += len;
	apply_width(ph, len, 0, count);
	if (ph->type == 'c')
		ft_putchar_fd(*ph->str, 1);
	else
		ft_putstr_fd(&ph->str[ph->offset], 1);
	apply_width(ph, len, 1, count);
}

static const char	*check_placeholder(const char *fmt, va_list *args,
	t_placeholder *ph)
{
	fmt = check_flags(fmt, ph);
	fmt = check_width(fmt, ph, args);
	fmt = check_precision(fmt, ph, args);
	fmt = check_length(fmt, ph);
	fmt = check_type(fmt, ph);
	return (fmt);
}

const char			*parse(const char *fmt, va_list *args, int *count)
{
	t_placeholder	*ph;

	if (!(ph = (t_placeholder *)malloc(sizeof(t_placeholder))))
	{
		*count = -1;
		return (fmt);
	}
	ph->error = (*count < 0) ? 1 : 0;
	fmt = check_placeholder(fmt, args, ph);
	if (ft_strchr("cspdiuxX%", ph->type))
	{
		apply_placeholder(args, count, ph);
		if (ph->error)
			*count = -1;
		if (ph->str && !ph->error)
			free(ph->str);
	}
	else
		*count = -1;
	free(ph);
	return (fmt);
}
