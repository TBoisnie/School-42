/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:19:18 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:20:34 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT_H
# define VECT_H

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

t_vect			vect_neg(t_vect u);

t_vect			vect_add(t_vect u, t_vect v);
t_vect			vect_sub(t_vect u, t_vect v);

t_vect			vect_scale(t_vect u, double scale);
t_vect			vect_rot_z(t_vect u, double angle);

double			vect_dot(t_vect u, t_vect v);
t_vect			vect_cross(t_vect u, t_vect v);

double			vect_length(t_vect u);
t_vect			vect_normalize(t_vect u);

#endif
