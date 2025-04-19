/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 17:26:30 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/26 08:01:09 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../memory/memory.h"
#include "exporter.h"

static void		set_info(t_export *e, unsigned char *header)
{
	header[14] = (unsigned char)(40);
	header[18] = (unsigned char)(e->width >> 0);
	header[19] = (unsigned char)(e->width >> 8);
	header[20] = (unsigned char)(e->width >> 16);
	header[21] = (unsigned char)(e->width >> 24);
	header[22] = (unsigned char)(e->height >> 0);
	header[23] = (unsigned char)(e->height >> 8);
	header[24] = (unsigned char)(e->height >> 16);
	header[25] = (unsigned char)(e->height >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(e->bpp * 8);
}

static void		set_head(t_export *e, unsigned char *header)
{
	int				file_size;

	file_size = 54 + (e->width * e->bpp + e->padding) * e->height;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(file_size >> 0);
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)(54);
}

unsigned char	*export_get_header(t_export *e)
{
	unsigned char	*header;

	if (!(header = malloc(54 * sizeof(unsigned char))))
		exit_error("Error\nExporter - Header (malloc).");
	mem_bzero(header, 54 * sizeof(unsigned char));
	set_head(e, header);
	set_info(e, header);
	return (header);
}
