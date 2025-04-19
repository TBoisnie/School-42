/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 23:19:25 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:12:19 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "../vect/vect.h"
# include "../texture/texture.h"

typedef struct	s_sprite
{
	t_vect		pos;
	t_vect		dist;

	t_texture	*texture;
}				t_sprite;

int				sprite_cmp(void *a, void *b);
t_sprite		*sprite_new(t_vect pos, t_vect dist, t_texture *texture);

#endif
