/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 08:02:22 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 11:03:50 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void		add_flag(const char c, t_placeholder *ph)
{
	if (c == '#')
		ph->flags |= (1 << 0);
	else if (c == '-')
	{
		ph->flags |= (1 << 1);
		remove_flag('0', ph);
	}
	else if (c == '0' && !has_flag('-', ph))
		ph->flags |= (1 << 2);
	else if (c == '+')
	{
		ph->flags |= (1 << 3);
		remove_flag(' ', ph);
	}
	else if (c == ' ' && !has_flag('+', ph))
		ph->flags |= (1 << 4);
	else if (c == '\'')
		ph->flags |= (1 << 5);
}

void		remove_flag(const char c, t_placeholder *ph)
{
	if (c == '#')
		ph->flags &= ~(1 << 0);
	else if (c == '-')
		ph->flags &= ~(1 << 1);
	else if (c == '0')
		ph->flags &= ~(1 << 2);
	else if (c == '+')
		ph->flags &= ~(1 << 3);
	else if (c == ' ')
		ph->flags &= ~(1 << 4);
	else if (c == '\'')
		ph->flags &= ~(1 << 5);
}

int			has_flag(const char c, t_placeholder *ph)
{
	if (c == '#')
		return (ph->flags & (1 << 0));
	if (c == '-')
		return (ph->flags & (1 << 1));
	if (c == '0')
		return (ph->flags & (1 << 2));
	if (c == '+')
		return (ph->flags & (1 << 3));
	if (c == ' ')
		return (ph->flags & (1 << 4));
	if (c == '\'')
		return (ph->flags & (1 << 5));
	return (0);
}

const char	*check_flags(const char *fmt, t_placeholder *ph)
{
	ph->flags = 0;
	while (ft_strchr("# 0+-'", *fmt))
		add_flag(*fmt++, ph);
	return (fmt);
}
