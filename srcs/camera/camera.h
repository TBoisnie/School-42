/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:54:08 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 09:29:54 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "../vect/vect.h"

typedef struct	s_camera
{
	t_vect	ray;

	t_vect	delta;
	t_vect	side;

	t_vect	screen;
}				t_camera;

#endif
