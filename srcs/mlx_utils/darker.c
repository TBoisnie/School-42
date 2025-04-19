/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 03:24:05 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 05:50:56 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../color/color.h"
#include "mlx_utils.h"

unsigned	darker(unsigned color, double dist)
{
	t_color	c;
	double	d;

	c.transparency = (color & 0xFF000000) >> 24;
	c.red = (color & 0x00FF0000) >> 16;
	c.green = (color & 0x0000FF00) >> 8;
	c.blue = (color & 0x000000FF) >> 0;
	d = 1.5 * dist + 1;
	c.red /= d;
	c.green /= d;
	c.blue /= d;
	return ((unsigned)color_to_int(c));
}
