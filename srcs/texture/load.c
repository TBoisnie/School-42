/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:05:14 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:17:30 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../cube3d.h"
#include "texture.h"

t_texture	texture_load(void *mlx, char *fpath)
{
	t_texture	texture;

	texture.image = mlx_xpm_file_to_image(mlx, fpath, &texture.width,
		&texture.height);
	if (!texture.image)
		exit_error("Error\nConfig file - Texture (not found).");
	return (texture);
}
