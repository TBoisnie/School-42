/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_to_bmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:03:05 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/26 08:42:42 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../string/string.h"
#include "../memory/memory.h"
#include "exporter.h"

void	export_to_bmp(t_config *c, void *image)
{
	t_export		e;
	int				fd;
	unsigned char	*str;

	if ((fd = open("screenshot.bmp", O_WRONLY | O_TRUNC | O_CREAT, 0644)) < 0)
		exit_error("Error\nExporter - File (open).");
	e.width = c->screen_width;
	e.height = c->screen_height;
	e.image = image;
	e.bpp = 3;
	e.padding = (4 - (c->screen_width * e.bpp % 4)) % 4;
	str = export_get_header(&e);
	write(fd, str, 54);
	free(str);
	str = export_get_image(&e);
	write(fd, str, (e.width * e.bpp + e.padding) * e.height);
	free(str);
	close(fd);
}
