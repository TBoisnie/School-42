/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 09:51:53 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 04:38:04 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

unsigned	darker(unsigned color, double dist);
unsigned	image_get(void *image, int x, int y);
void		image_set(void *image, int x, int y, unsigned color);

#endif
