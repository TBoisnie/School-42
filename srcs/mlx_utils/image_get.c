/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 09:53:28 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 12:55:21 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "mlx_utils.h"

unsigned	image_get(void *image, int x, int y)
{
	int			bpp;
	int			sline;
	int			endian;
	unsigned	*addr;

	addr = (unsigned*)mlx_get_data_addr(image, &bpp, &sline, &endian);
	sline /= sizeof(unsigned);
	bpp /= (8 * sizeof(unsigned));
	return (addr[y * sline + x * bpp]);
}
