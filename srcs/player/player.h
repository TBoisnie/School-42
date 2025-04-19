/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:14:02 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:09:16 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "../vect/vect.h"
# include "../camera/camera.h"
# include "../world/world.h"

typedef struct	s_player
{
	t_vect		pos;
	t_vect		dir;

	t_vect		pos_map;

	t_camera	camera;

	double		move_speed;
	double		rotation_speed;
}				t_player;

void			player_move(t_world *world, t_player *player, double speed);
void			player_strafe(t_world *world, t_player *player, double speed);
void			player_rotate(t_player *player, double speed);

#endif
