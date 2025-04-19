/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:56:51 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:18:33 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vect.h"

double	vect_length(t_vect u)
{
	double	length;

	length = sqrt(vect_dot(u, u));
	return (length);
}
