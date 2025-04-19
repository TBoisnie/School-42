/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:25:42 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/16 03:56:14 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../char/char.h"
#include "parser.h"

void	parse_texture(t_config *c, char *line, t_texture_index index)
{
	if (!char_is_space(*line))
		exit_error("Error\nParse - Texture (space).");
	while (char_is_space(*line))
		line++;
	if (!c->world.textures[index].image)
		c->world.textures[index] = texture_load(c->mlx, line);
	else
		exit_error("Error\nParse - Texture (redifined).");
}
