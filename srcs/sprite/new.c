/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:22:22 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:12:35 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../cube3d.h"
#include "sprite.h"

t_sprite	*sprite_new(t_vect pos, t_vect dist, t_texture *texture)
{
	t_sprite	*sprite;

	if (!(sprite = (t_sprite *)malloc(sizeof(t_sprite))))
		exit_error("Error.\nSprite malloc fail.");
	sprite->pos = pos;
	sprite->dist = dist;
	sprite->texture = texture;
	return (sprite);
}
