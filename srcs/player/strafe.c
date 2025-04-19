/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 16:00:26 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:06:49 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "player.h"

void	player_strafe(t_world *world, t_player *player, double speed)
{
	int	p;
	int	sign;

	sign = (player->dir.y > 0) ? -1 : 1;
	p = (int)player->pos.y * world->width
		+ (int)(player->pos.x + (1 - fabs(player->dir.x)) * speed * sign);
	if (world->map[p] != '1')
		player->pos.x += (1 - fabs(player->dir.x)) * speed * sign;
	sign = (player->dir.x < 0) ? -1 : 1;
	p = (int)(player->pos.y + (1 - fabs(player->dir.y)) * speed * sign)
		* world->width + (int)(player->pos.x);
	if (world->map[p] != '1')
		player->pos.y += (1 - fabs(player->dir.y)) * speed * sign;
}
