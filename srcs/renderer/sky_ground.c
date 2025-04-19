/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_ground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:24:12 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 05:50:05 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../mlx_utils/mlx_utils.h"
#include "../color/color.h"
#include "renderer.h"

void	render_sky_ground(t_config *c, void *image)
{
	int	x;
	int y;

	y = -1;
	while (++y < c->screen_height)
	{
		x = -1;
		while (++x < c->screen_width)
			image_set(image, x, y, mlx_get_color_value(c->mlx,
				(y < c->screen_height / 2)
					? darker(color_to_int(c->world.sky), 0.2 + y * 0.02)
					: darker(color_to_int(c->world.ground), 0.2 + 0.02 *
						(c->screen_height - y))));
	}
}
