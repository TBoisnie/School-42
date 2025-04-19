/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 07:21:51 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 07:21:52 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vect	vect_normalize(t_vect u)
{
	double	length;
	t_vect	w;

	length = vect_length(u);
	w.x = u.x / length;
	w.y = u.y / length;
	w.z = u.z / length;
	return (w);
}
