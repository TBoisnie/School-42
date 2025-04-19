/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 02:21:29 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 03:09:41 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../mlx_utils/mlx_utils.h"
#include "renderer.h"

void	render_hud(t_config *c, void *image)
{
	int			x;
	int			y;
	unsigned	color;

	x = -1;
	while (++x < c->world.textures[HUD].width)
	{
		y = -1;
		while (++y < c->world.textures[HUD].height)
		{
			color = image_get(c->world.textures[HUD].image, x, y);
			if ((color & 0x00FFFFFF) != 0)
				image_set(image,
					(c->screen_width - c->world.textures[HUD].width) / 2 + x,
					(c->screen_height - c->world.textures[HUD].height) / 2 + y,
					mlx_get_color_value(c->mlx, color));
		}
	}
}
