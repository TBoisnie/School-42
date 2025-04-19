/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 07:21:17 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 07:21:18 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"

double	vect_length(t_vect u)
{
	double	length;

	length = sqrt(vect_dot(u, u));
	return (length);
}
