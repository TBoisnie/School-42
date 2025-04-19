/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:23:06 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/22 15:29:35 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../string/string.h"
#include "../char/char.h"
#include "../memory/memory.h"
#include "parser.h"

static void	uniform_width(t_config *c, int width)
{
	int		h;
	char	*new_map;

	h = -1;
	if (!(new_map = malloc((c->world.height * width + 1) * sizeof(char))))
		exit_error("Error\nParser - World (malloc uniform).");
	mem_set(new_map, ' ', c->world.height * width);
	new_map[c->world.height * width] = '\0';
	while (++h < c->world.height)
		mem_copy(&new_map[h * width], &c->world.map[h * c->world.width],
			c->world.width);
	free(c->world.map);
	c->world.map = new_map;
	c->world.width = width;
}

static void	set_world(t_config *c, int width, char *row)
{
	char *tmp;

	if (c->world.width == 0)
		c->world.width = width;
	if (width > c->world.width)
		uniform_width(c, width);
	tmp = c->world.map;
	c->world.map = str_join(c->world.map, row);
	free(tmp);
	while (width++ < c->world.width)
	{
		tmp = c->world.map;
		c->world.map = str_join_char(c->world.map, ' ');
		free(tmp);
	}
	c->world.height++;
	free(row);
}

static char	*get_row(t_config *c, char *line, char *row, int *width)
{
	char	*tmp;

	while (*line)
	{
		if (str_contains(" 012NSEW", *line))
		{
			tmp = row;
			row = str_contains(" 012", *line)
				? str_join_char(row, *line) : str_join_char(row, '0');
			free(tmp);
			if (str_contains("NSEW", *line))
				set_player(c, *line, *width);
			else if (*line == '2')
				set_sprite(c, *width);
			(*width)++;
			line++;
		}
		else
			exit_error("Error\nParser - World (invalid id).");
	}
	return (row);
}

void		parse_world(t_config *c, int fd, char **line, ssize_t *c_read)
{
	char	*row;
	int		width;

	while (*c_read >= 0)
	{
		width = 0;
		row = NULL;
		row = get_row(c, *line, row, &width);
		set_world(c, width, row);
		if (*c_read == 0)
			break ;
		free(*line);
		*c_read = get_next_line(fd, line);
	}
	if (*c_read < 0)
		exit_error("Error\nParser - World (read).");
	valid_wall(c);
}
