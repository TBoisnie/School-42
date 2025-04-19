/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 23:40:04 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 03:12:44 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../renderer/renderer.h"
#include "../cube3d.h"
#include "event.h"

int	event_handle_loop(t_config *c)
{
	if (c->key_pressed[0])
		player_move(&c->world, &c->player, c->player.move_speed);
	if (c->key_pressed[1])
		player_move(&c->world, &c->player, -c->player.move_speed);
	if (c->key_pressed[2])
		player_strafe(&c->world, &c->player, -c->player.move_speed);
	if (c->key_pressed[3])
		player_strafe(&c->world, &c->player, c->player.move_speed);
	if (c->key_pressed[4])
		player_rotate(&c->player, -c->player.rotation_speed);
	if (c->key_pressed[5])
		player_rotate(&c->player, c->player.rotation_speed);
	render(c);
	return (0);
}
