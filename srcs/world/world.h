/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 06:55:51 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 03:10:13 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "../list/list.h"
# include "../color/color.h"
# include "../texture/texture.h"

# define NB_TEXTURE	6

typedef enum	e_texture_index
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	SPRITE,
	HUD
}				t_texture_index;

typedef struct	s_world
{
	int			width;
	int			height;

	char		*map;

	t_color		sky;
	t_color		ground;
	t_list		*sprites;
	t_texture	textures[NB_TEXTURE];
}				t_world;

#endif
