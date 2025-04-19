/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 07:22:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 07:22:20 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vect	vect_scale(t_vect u, double scale)
{
	t_vect	w;

	w.x = u.x * scale;
	w.y = u.y * scale;
	w.z = u.z * scale;
	return (w);
}
