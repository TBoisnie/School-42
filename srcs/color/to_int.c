/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:17:43 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 09:28:58 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	color_to_int(t_color color)
{
	int	c;

	c = 0x0;
	c += color.transparency << 24;
	c += color.red << 16;
	c += color.green << 8;
	c += color.blue << 0;
	return (c);
}
