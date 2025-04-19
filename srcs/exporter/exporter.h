/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exporter.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 11:54:07 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/26 08:19:49 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORTER_H
# define EXPORTER_H

# include "../cube3d.h"

typedef struct	s_export
{
	int		width;
	int		height;
	int		padding;
	int		bpp;

	void	*image;
}				t_export;

void			export_to_bmp(t_config *c, void *image);

unsigned char	*export_get_header(t_export *e);
unsigned char	*export_get_image(t_export *e);

#endif
