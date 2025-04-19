/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:27:30 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:07:00 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	player_move(t_world *world, t_player *player, double speed)
{
	int	p;

	p = (int)(player->pos.y) * world->width
		+ (int)(player->pos.x + player->dir.x * speed);
	if (world->map[p] != '1')
		player->pos.x += player->dir.x * speed;
	p = (int)(player->pos.y + player->dir.y * speed) * world->width
		+ (int)(player->pos.x);
	if (world->map[p] != '1')
		player->pos.y += player->dir.y * speed;
}
