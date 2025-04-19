/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_length.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 09:28:20 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 05:51:57 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*check_length(const char *fmt, t_placeholder *ph)
{
	ph->length = '\0';
	if (*fmt == 'h')
	{
		if (*++fmt == 'h')
		{
			ph->length = 'H';
			++fmt;
		}
		else
			ph->length = 'h';
	}
	else if (*fmt == 'l')
	{
		if (*++fmt == 'l')
		{
			ph->length = 'L';
			++fmt;
		}
		else
			ph->length = 'l';
	}
	return (fmt);
}
