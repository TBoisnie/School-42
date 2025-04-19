/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:15:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/22 15:41:24 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <mlx.h>
#include "memory/memory.h"
#include "renderer/renderer.h"
#include "parser/parser.h"
#include "event/event.h"
#include "sprite/sprite.h"
#include "cube3d.h"

static int	str_equals(char *a, char *b)
{
	while (*a && *b && *a++ == *b++)
		;
	return ((int)(!*a && !*b));
}

static void	valid_config(t_config *c)
{
	if (c->player.pos.z != 0)
		exit_error("Error\nConfig - Player (not def).");
	if (!c->world.textures[NORTH].image)
		exit_error("Error\nConfig - Texture (north).");
	if (!c->world.textures[SOUTH].image)
		exit_error("Error\nConfig - Texture (south).");
	if (!c->world.textures[EAST].image)
		exit_error("Error\nConfig - Texture (east).");
	if (!c->world.textures[WEST].image)
		exit_error("Error\nConfig - Texture (west).");
	if (!c->world.textures[SPRITE].image)
		exit_error("Error\nConfig - Texture (sprite).");
	if (c->world.sky.transparency != 0)
		exit_error("Error\nConfig - Color (sky).");
	if (c->world.ground.transparency != 0)
		exit_error("Error\nConfig - Color (ground).");
}

static void	init_config(t_config *c)
{
	c->screen_width = 0;
	c->screen_height = 0;
	mem_bzero(c->key_pressed, 6 * sizeof(int) / sizeof(unsigned char));
	c->player.pos = (t_vect){0, 0, 1};
	c->player.dir = (t_vect){0, 0, 0};
	c->player.camera.screen = (t_vect){0, 0, 0};
	c->player.move_speed = 0.155;
	c->player.rotation_speed = 0.155;
	c->world.width = 0;
	c->world.height = 0;
	c->world.map = NULL;
	c->world.sprites = NULL;
	c->world.sky = (t_color){0, 0, 0, 255};
	c->world.ground = (t_color){0, 0, 0, 255};
	c->world.textures[NORTH].image = NULL;
	c->world.textures[SOUTH].image = NULL;
	c->world.textures[EAST].image = NULL;
	c->world.textures[WEST].image = NULL;
	c->world.textures[SPRITE].image = NULL;
	c->world.textures[HUD] = texture_load(c->mlx, "./images/Cursor.xpm");
}

int			main(int argc, char *argv[])
{
	t_config	c;

	if (argc < 2 || argc > 3)
		exit_error("Error\nInvalid argument count.");
	c.save = 0;
	if (argc == 3 && !(c.save = str_equals(argv[2], "--save")))
		exit_error("Error\nInvalid --save argument.");
	if (!(c.mlx = mlx_init()))
		exit_error("Error\nMlx initialisation failed.");
	init_config(&c);
	parse(&c, argv[1]);
	valid_config(&c);
	if (!c.save)
	{
		if (!(c.window = mlx_new_window(c.mlx, c.screen_width, c.screen_height,
			"Cub3D")))
			exit_error("Error\nMlx window creation failed.");
		render(&c);
		mlx_hook(c.window, 2, 1L << 0, event_handle_key_pressed, &c);
		mlx_hook(c.window, 3, 1L << 1, event_handle_key_released, &c);
		mlx_hook(c.window, 17, 1L << 17, event_handle_window, &c);
		mlx_loop_hook(c.mlx, event_handle_loop, &c);
		mlx_loop(c.mlx);
	}
	return (render(&c));
}
