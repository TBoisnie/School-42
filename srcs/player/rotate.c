/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 10:42:33 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:06:56 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	player_rotate(t_player *player, double speed)
{
	player->dir = vect_rot_z(player->dir, speed);
	player->camera.screen = vect_rot_z(player->camera.screen, speed);
}
