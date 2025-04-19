/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_z.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 07:22:06 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 07:22:07 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

t_vect	vect_rot_z(t_vect u, double angle)
{
	t_vect	w;

	w.x = u.x * cos(angle) - u.y * sin(angle);
	w.y = u.x * sin(angle) + u.y * cos(angle);
	w.z = u.z;
	return (w);
}
