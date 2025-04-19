/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:36:09 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/10 22:33:28 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../string/string.h"
#include "parser.h"

static void	check_wall(t_config *c, int map_len, int i)
{
	if (c->world.map[i] == ' ')
	{
		if (i >= c->world.width
			&& !str_contains(" 1", c->world.map[i - c->world.width]))
			exit_error("Error\nParser - Wall (space up).");
		if (i < map_len - c->world.width
			&& !str_contains(" 1", c->world.map[i + c->world.width]))
			exit_error("Error\nParser - Wall (space down).");
		if (i % c->world.width < c->world.width - 1
			&& !str_contains(" 1", c->world.map[i + 1]))
			exit_error("Error\nParser - Wall (space right).");
		if (i % c->world.width > 0 && !str_contains(" 1", c->world.map[i - 1]))
			exit_error("Error\nParser - Wall (space left).");
	}
	if (!str_contains(" 1", c->world.map[i]))
	{
		if (i < c->world.width)
			exit_error("Error\nParser - Wall (top).");
		if (i % c->world.width == 0)
			exit_error("Error\nParser - Wall (left).");
		if (i % c->world.width == c->world.width - 1)
			exit_error("Error\nParser - Wall (right).");
		if (i > map_len - c->world.width)
			exit_error("Error\nParser - Wall (bottom).");
	}
}

void		valid_wall(t_config *c)
{
	int	i;
	int map_len;

	map_len = (int)str_length(c->world.map);
	i = -1;
	if (c->world.map == NULL)
		exit_error("Error\nParser - World (empty).");
	while (c->world.map[++i])
		check_wall(c, map_len, i);
}
