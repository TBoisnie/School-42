/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:36:56 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/27 10:40:16 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

const char	*check_type(const char *fmt, t_placeholder *ph)
{
	ph->type = '_';
	if (*fmt != '\0' && ft_strchr("cspdiuxXfegn%", *fmt))
	{
		ph->type = *fmt;
		if (ph->type == 'p')
			add_flag('#', ph);
		if (ph->has_dot && ft_strchr("pdiuxX", ph->type))
			remove_flag('0', ph);
		++fmt;
	}
	return (fmt);
}
