/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:37:00 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/26 08:46:50 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../mlx_utils/mlx_utils.h"
#include "../memory/memory.h"
#include "exporter.h"

unsigned char			*export_get_image(t_export *e)
{
	unsigned char	*image;
	int				x;
	int				y;
	unsigned char	*cursor;
	unsigned int	color;

	if (!(image = malloc((e->width * e->bpp + e->padding) * e->height
		* sizeof(unsigned char))))
		exit_error("Error\nExporter - Image (malloc).");
	cursor = image;
	y = -1;
	while (++y < e->height)
	{
		x = -1;
		while (++x < e->width)
		{
			color = image_get(e->image, x, e->height - 1 - y);
			*cursor++ = (unsigned char)(color >> 0);
			*cursor++ = (unsigned char)(color >> 8);
			*cursor++ = (unsigned char)(color >> 16);
		}
		mem_copy(cursor, "\0\0\0", e->padding);
		cursor += e->padding;
	}
	return (image);
}
