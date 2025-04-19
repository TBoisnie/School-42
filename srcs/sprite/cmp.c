/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 13:11:39 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:13:05 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

int	sprite_cmp(void *a, void *b)
{
	t_sprite	*sp_a;
	t_sprite	*sp_b;

	sp_a = a;
	sp_b = b;
	return (vect_length(sp_a->dist) >= vect_length(sp_b->dist) ? -1 : 1);
}
