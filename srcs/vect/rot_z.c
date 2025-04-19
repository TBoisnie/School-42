/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_z.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:41:43 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:19:05 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vect.h"

t_vect	vect_rot_z(t_vect u, double angle)
{
	t_vect	w;

	w.x = u.x * cos(angle) - u.y * sin(angle);
	w.y = u.x * sin(angle) + u.y * cos(angle);
	w.z = u.z;
	return (w);
}
