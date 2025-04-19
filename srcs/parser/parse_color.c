/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:20:10 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/16 03:47:19 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../string/string.h"
#include "../char/char.h"
#include "parser.h"

void	parse_color(t_config *c, char *line, int sky)
{
	t_color	*color;

	if (!char_is_space(*line))
		exit_error("Error\nParse - Color (space).");
	while (char_is_space(*line))
		line++;
	color = sky ? &c->world.sky : &c->world.ground;
	if (color->transparency == 0)
		exit_error("Error\nParse - Color (redefined).");
	color->transparency = 0;
	line = str_to_int(line, &color->red);
	(*line == ',') ? line++ : exit_error("Error\nParse - Color (comma).");
	line = str_to_int(line, &color->green);
	(*line == ',') ? line++ : exit_error("Error\nParse - Color (comma).");
	line = str_to_int(line, &color->blue);
	while (char_is_space(*line))
		line++;
	if (*line || color->red < 0 || color->green < 0 || color->blue < 0
		|| color->red > 255 || color->green > 255 || color->blue > 255)
		exit_error("Error\nParse - Color (value).");
}
