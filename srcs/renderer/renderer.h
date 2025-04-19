/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:21:16 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 03:08:17 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "../sprite/sprite.h"
# include "../cube3d.h"

typedef struct	s_garbage_map
{
	t_vect			step;
	t_texture_index	side;
	double			wall_dist;
	int				wall_height;
	double			wall_x;
	int				tex_x;
	double			tex_y;
	int				y_min;
	int				y_max;
	double			y_step;
}				t_garbage_map;

typedef struct	s_garbage_sprites
{
	void		*image;
	t_list		*item;
	t_sprite	*sprite;
	double		inv_det;
	double		tx;
	double		ty;
	int			sprite_width;
	int			sprite_height;
	int			sprite_x;
	int			x_min;
	int			x_max;
	int			y_min;
	int			y_max;
	int			tex_x;
	int			tex_y;
}				t_garbage_sprites;

void			render_sky_ground(t_config *c, void *image);
void			render_map(t_config *c, void *image, double z_buffer[]);
void			render_sprites(t_config *c, void *image, double z_buffer[]);
void			render_hud(t_config *c, void *image);

int				render(t_config *c);

#endif
