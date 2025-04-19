/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:57:03 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/10 20:07:43 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../string/string.h"
#include "../char/char.h"
#include "parser.h"

static int	check_file_ext(char *filepath, char *ext)
{
	int		plen;
	int		elen;

	plen = 0;
	while (*filepath)
	{
		plen++;
		filepath++;
	}
	elen = 0;
	while (*ext)
	{
		elen++;
		ext++;
	}
	while (elen > 0 && plen > 0)
	{
		if (*ext-- != *filepath--)
			return (0);
		elen--;
		plen--;
	}
	return ((elen == 0));
}

static void	if_forest(t_config *c, char **line, int fd, ssize_t *c_read)
{
	size_t	offset;

	offset = 0;
	while (char_is_space(*(*line + offset)))
		offset++;
	if (*(*line + offset) == 'R')
		parse_definition(c, *line + offset + 1);
	else if (*(*line + offset) == 'N' && *(*line + offset + 1) == 'O')
		parse_texture(c, *line + offset + 2, NORTH);
	else if (*(*line + offset) == 'S' && *(*line + offset + 1) == 'O')
		parse_texture(c, *line + offset + 2, SOUTH);
	else if (*(*line + offset) == 'W' && *(*line + offset + 1) == 'E')
		parse_texture(c, *line + offset + 2, WEST);
	else if (*(*line + offset) == 'E' && *(*line + offset + 1) == 'A')
		parse_texture(c, *line + offset + 2, EAST);
	else if (*(*line + offset) == 'S')
		parse_texture(c, *line + offset + 1, SPRITE);
	else if (*(*line + offset) == 'F')
		parse_color(c, *line + offset + 1, 1);
	else if (*(*line + offset) == 'C')
		parse_color(c, *line + offset + 1, 0);
	else if (*(*line + offset) == '1')
		parse_world(c, fd, line, c_read);
	else
		exit_error("Error\nParser - Identifier (unknown).");
}

void		parse(t_config *c, char *filepath)
{
	char	*line;
	int		fd;
	ssize_t	c_read;

	if (!check_file_ext(filepath, ".cub"))
		exit_error("Error\nParser - File (extension).");
	if ((fd = open(filepath, O_RDONLY)) == -1)
		exit_error("Error\nParser - File (open).");
	while ((c_read = get_next_line(fd, &line)) >= 0)
	{
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		if_forest(c, &line, fd, &c_read);
		if (c_read == 0)
			break ;
		free(line);
	}
	free(line);
	close(fd);
}
