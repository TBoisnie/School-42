/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 08:19:24 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 03:07:53 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../exporter/exporter.h"
#include "renderer.h"

int	render(t_config *c)
{
	void	*image;
	double	z_buffer[c->screen_width];

	image = mlx_new_image(c->mlx, c->screen_width, c->screen_height);
	render_sky_ground(c, image);
	render_map(c, image, z_buffer);
	render_sprites(c, image, z_buffer);
	render_hud(c, image);
	if (c->save)
		export_to_bmp(c, image);
	else
	{
		mlx_clear_window(c->mlx, c->window);
		mlx_put_image_to_window(c->mlx, c->window, image, 0, 0);
	}
	mlx_destroy_image(c->mlx, image);
	return (0);
}
