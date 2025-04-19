/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:01:18 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 14:16:16 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

void	apply_flags(t_placeholder *ph)
{
	char	*tmp;

	tmp = ph->str;
	if (has_flag('#', ph) && ft_strchr("pxX", ph->type))
	{
		if ((ph->str = ft_strjoin((ph->type == 'X') ? "0X" : "0x", tmp)))
			free(tmp);
		else
			ph->error = 1;
	}
	if ((has_flag('+', ph) || has_flag(' ', ph))
		&& ft_strchr("di", ph->type) && ph->value >= 0)
	{
		if ((ph->str = ft_strjoin(has_flag('+', ph) ? "+" : " ", tmp)))
			free(tmp);
		else
			ph->error = 1;
	}
}
