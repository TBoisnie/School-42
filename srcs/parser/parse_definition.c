/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_definition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:16:27 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/22 14:19:34 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
#include "../math/math.h"
#include "../string/string.h"
#include "../char/char.h"
#include "parser.h"

void	parse_definition(t_config *c, char *line)
{
	if (c->screen_width != 0)
		exit_error("Error\nParse - Definition (redefined).");
	if (!char_is_space(*line))
		exit_error("Error\nParse - Definition (space).");
	while (char_is_space(*line))
		line++;
	line = str_to_int(line, &c->screen_width);
	if (!char_is_space(*line))
		exit_error("Error\nParse - Definition (space).");
	while (char_is_space(*line))
		line++;
	line = str_to_int(line, &c->screen_height);
	while (char_is_space(*line))
		line++;
	c->screen_width = math_int_min(c->screen_width, 1920);
	c->screen_height = math_int_min(c->screen_height, 1080);
	if (*line || c->screen_width <= 0 || c->screen_height <= 0)
		exit_error("Error\nParse - Definition (value).");
}
