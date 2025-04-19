/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 10:01:03 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 12:55:12 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlx_utils.h"

void	image_set(void *image, int x, int y, unsigned color)
{
	int			bpp;
	int			sline;
	int			endian;
	unsigned	*addr;

	addr = (unsigned*)mlx_get_data_addr(image, &bpp, &sline, &endian);
	sline /= sizeof(unsigned);
	bpp /= (8 * sizeof(unsigned));
	addr[y * sline + x * bpp] = color;
}
