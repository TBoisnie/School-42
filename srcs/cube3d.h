/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:06:00 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 03:12:04 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "player/player.h"
# include "world/world.h"

typedef struct	s_config
{
	void		*mlx;
	void		*window;

	int			key_pressed[6];

	int			screen_width;
	int			screen_height;

	int			save;

	t_player	player;
	t_world		world;
}				t_config;

void			exit_success(void);
void			exit_error(char *message);

#endif
