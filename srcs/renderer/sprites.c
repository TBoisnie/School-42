/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:34:07 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 05:50:12 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include "../mlx_utils/mlx_utils.h"
#include "../math/math.h"
#include "renderer.h"

static void	sort_sprites(t_config *c, t_garbage_sprites *g)
{
	g->item = c->world.sprites;
	while (g->item)
	{
		g->sprite = g->item->content;
		g->sprite->dist = vect_sub(g->sprite->pos, c->player.pos);
		g->item = g->item->next;
	}
	c->world.sprites = list_sort(c->world.sprites, sprite_cmp);
}

static void	update_geometry(t_config *c, t_garbage_sprites *g)
{
	g->tx = g->inv_det * (
		c->player.dir.y * g->sprite->dist.x -
		c->player.dir.x * g->sprite->dist.y);
	g->ty = g->inv_det * (
		-c->player.camera.screen.y * g->sprite->dist.x +
		c->player.camera.screen.x * g->sprite->dist.y);
	g->sprite_width = (int)fabs(c->screen_height / g->ty);
	g->sprite_height = (int)fabs(c->screen_height / g->ty);
	g->sprite_x = (int)((c->screen_width / 2) *
		(1 + g->tx / g->ty));
	g->y_min = math_int_max(-g->sprite_height / 2 +
		c->screen_height / 2, 0);
	g->y_max = math_int_min(g->sprite_height / 2 +
		c->screen_height / 2, c->screen_height);
	g->x_min = math_int_max(-g->sprite_width / 2 +
		g->sprite_x, 0);
	g->x_max = math_int_min(g->sprite_width / 2 +
		g->sprite_x, c->screen_width - 1);
}

static void	draw(t_config *c, t_garbage_sprites *g, double z, int x)
{
	int	y;
	int	d;
	int	color;

	g->tex_x = (int)((x - (-g->sprite_width / 2 + g->sprite_x)) *
		g->sprite->texture->width / g->sprite_width);
	if (g->ty > 0 && x > 0 && x < c->screen_width && g->ty < z)
	{
		y = g->y_min - 1;
		while (++y < g->y_max)
		{
			d = (y) * 256 - c->screen_height * 128 + g->sprite_height * 128;
			g->tex_y = ((d * g->sprite->texture->height) /
				g->sprite_height) / 256;
			color = image_get(g->sprite->texture->image, g->tex_x, g->tex_y);
			if ((color & 0x00FFFFFF) != 0)
				image_set(g->image, x, y, mlx_get_color_value(c->mlx,
					darker(color, g->ty)));
		}
	}
}

void		render_sprites(t_config *c, void *image, double z_buffer[])
{
	int					x;
	t_garbage_sprites	g;

	g.image = image;
	sort_sprites(c, &g);
	g.inv_det = 1.0 / (c->player.camera.screen.x * c->player.dir.y -
		c->player.dir.x * c->player.camera.screen.y);
	g.item = c->world.sprites;
	while (g.item)
	{
		g.sprite = g.item->content;
		update_geometry(c, &g);
		x = g.x_min - 1;
		while (++x < g.x_max)
			draw(c, &g, z_buffer[x], x);
		g.item = g.item->next;
	}
}
