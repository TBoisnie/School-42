/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:55:45 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:18:53 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect.h"

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
