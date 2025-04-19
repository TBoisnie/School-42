/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 22:18:58 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/22 15:53:50 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../list/list.h"
#include "../sprite/sprite.h"
#include "parser.h"

void	set_sprite(t_config *c, int x)
{
	t_list	*item;

	item = list_new(sprite_new(
			(t_vect){0.5 + x, 0.5 + c->world.height, 0},
			(t_vect){0, 0, 0},
			&c->world.textures[SPRITE]));
	if (!item)
		exit_error("Error.\nParser - World (set sprite malloc failed).");
	c->world.sprites = list_append(c->world.sprites, item);
}

void	set_player(t_config *c, char dir, int x)
{
	if (c->player.pos.z == 0)
		exit_error("Error\nParser - World (player redefined).");
	c->player.pos = (t_vect){0.5 + x, 0.5 + c->world.height, 0};
	if (dir == 'N' || dir == 'S')
	{
		c->player.dir = (dir == 'N')
			? (t_vect){0, -1, 0} : (t_vect){0, 1, 0};
		c->player.camera.screen = (dir == 'N')
			? (t_vect){0.66, 0, 0} : (t_vect){-0.66, 0, 0};
	}
	else
	{
		c->player.dir = (dir == 'E')
			? (t_vect){1, 0, 0} : (t_vect){-1, 0, 0};
		c->player.camera.screen = (dir == 'E')
			? (t_vect){0, 0.66, 0} : (t_vect){0, -0.66, 0};
	}
}
