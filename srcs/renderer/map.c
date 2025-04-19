/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:28:27 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/22 23:02:12 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../mlx_utils/mlx_utils.h"
#include <math.h>
#include "../math/math.h"
#include "renderer.h"

static void	update_player(t_config *c, int x, t_garbage_map *g)
{
	c->player.pos_map = (t_vect){
		(int)c->player.pos.x, (int)c->player.pos.y, (int)c->player.pos.z};
	c->player.camera.ray = vect_add(
		c->player.dir, vect_scale(c->player.camera.screen,
			2 * x / (double)c->screen_width - 1));
	c->player.camera.delta = (t_vect){
		fabs(1 / c->player.camera.ray.x),
		fabs(1 / c->player.camera.ray.y), 0};
	g->step = (t_vect){
		c->player.camera.ray.x < 0 ? -1 : 1,
		c->player.camera.ray.y < 0 ? -1 : 1, 0};
	c->player.camera.side.x = c->player.camera.delta.x;
	c->player.camera.side.x *= c->player.camera.ray.x < 0 ?
		c->player.pos.x - ((int)c->player.pos_map.x) :
		((int)c->player.pos_map.x) + 1.0 - c->player.pos.x;
	c->player.camera.side.y = c->player.camera.delta.y;
	c->player.camera.side.y *= c->player.camera.ray.y < 0 ?
		c->player.pos.y - ((int)c->player.pos_map.y) :
		((int)c->player.pos_map.y) + 1.0 - c->player.pos.y;
	c->player.camera.side.z = 0;
}

static void	update_wall_side(t_config *c, t_garbage_map *g)
{
	int	hit;

	hit = 0;
	g->side = NORTH;
	while (hit == 0)
	{
		if (c->player.camera.side.x < c->player.camera.side.y)
		{
			c->player.camera.side.x += c->player.camera.delta.x;
			c->player.pos_map.x += ((int)g->step.x);
			g->side = (c->player.pos_map.x - c->player.pos.x <= 0)
				? WEST : EAST;
		}
		else
		{
			c->player.camera.side.y += c->player.camera.delta.y;
			c->player.pos_map.y += ((int)g->step.y);
			g->side = (c->player.pos_map.y - c->player.pos.y <= 0)
				? NORTH : SOUTH;
		}
		if (c->world.map[((int)c->player.pos_map.y) * c->world.width
			+ ((int)c->player.pos_map.x)] == '1')
			hit = 1;
	}
}

static void	update_wall(t_config *c, t_garbage_map *g)
{
	if (g->side == EAST || g->side == WEST)
	{
		g->wall_dist = (((int)c->player.pos_map.x) - c->player.pos.x +
			(1 - ((int)g->step.x)) / 2) / c->player.camera.ray.x;
		g->wall_x = c->player.pos.y + g->wall_dist * c->player.camera.ray.y;
	}
	else
	{
		g->wall_dist = (((int)c->player.pos_map.y) - c->player.pos.y +
			(1 - ((int)g->step.y)) / 2) / c->player.camera.ray.y;
		g->wall_x = c->player.pos.x + g->wall_dist * c->player.camera.ray.x;
	}
	g->wall_height = (int)(c->screen_height / g->wall_dist);
	g->wall_x -= floor(g->wall_x);
}

static void	update_texture(t_config *c, t_garbage_map *g)
{
	g->y_min = math_int_max(-g->wall_height / 2 + c->screen_height / 2, 0);
	g->y_max = math_int_min(g->wall_height / 2 + c->screen_height / 2,
			c->screen_height);
	g->y_step = 1.0 * c->world.textures[g->side].height / g->wall_height;
	g->tex_x = (int)(g->wall_x * (double)c->world.textures[g->side].width);
	if (g->side == EAST || g->side == WEST)
		if (c->player.camera.ray.x < 0)
			g->tex_x = c->world.textures[g->side].width - g->tex_x - 1;
	if (g->side == NORTH || g->side == SOUTH)
		if (c->player.camera.ray.y > 0)
			g->tex_x = c->world.textures[g->side].width - g->tex_x - 1;
	g->tex_y = (g->y_min - c->screen_height / 2 + g->wall_height / 2) *
		g->y_step;
}

void		render_map(t_config *c, void *image, double z_buffer[])
{
	int				x;
	int				y;
	t_garbage_map	g;

	x = -1;
	while (++x < c->screen_width)
	{
		update_player(c, x, &g);
		update_wall_side(c, &g);
		update_wall(c, &g);
		z_buffer[x] = g.wall_dist;
		update_texture(c, &g);
		y = g.y_min - 1;
		while (++y < g.y_max)
		{
			image_set(image, x, y, mlx_get_color_value(c->mlx, darker(image_get(
				c->world.textures[g.side].image, g.tex_x, (int)g.tex_y),
				g.wall_dist)));
			g.tex_y += g.y_step;
		}
	}
}
