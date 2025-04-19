/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:39:41 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:19:19 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"

t_vect	vect_scale(t_vect u, double scale)
{
	t_vect	w;

	w.x = u.x * scale;
	w.y = u.y * scale;
	w.z = u.z * scale;
	return (w);
}
