/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 06:27:16 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:17:01 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct	s_texture
{
	int		width;
	int		height;

	void	*image;
}				t_texture;

t_texture		texture_load(void *mlx, char *fpath);

#endif
