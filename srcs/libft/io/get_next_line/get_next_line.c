/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:16:18 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:23:37 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../../string/string.h"
#include "get_next_line.h"

static int	read_line(t_buffer_list *node, char **line, char **str, char *tmp)
{
	ssize_t	c_read;
	char	*back_n;

	while ((node->position != 0 && (c_read = BUFFER_SIZE))
		|| (c_read = read(node->fd, node->buffer, BUFFER_SIZE)) > 0)
	{
		node->buffer[c_read] = '\0';
		if ((back_n = str_chr(&node->buffer[node->position], '\n')) != NULL)
			*back_n = '\0';
		tmp = *str;
		if (!(*str = str_join(*str, &node->buffer[node->position])))
		{
			free(tmp);
			return (-1);
		}
		*line = *str;
		free(tmp);
		if (back_n != NULL)
		{
			node->position = (int)(back_n - node->buffer + 1);
			return (1);
		}
		node->position = 0;
	}
	return ((int)c_read);
}

int			get_next_line(const int fd, char **line)
{
	static t_buffer_list	*list;
	t_buffer_list			*node;
	char					*str;
	char					*tmp;
	int						result;

	tmp = NULL;
	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0
		|| !(str = malloc(sizeof(char)))
		|| !(node = get_buffer_fd(&list, fd)))
		return (-1);
	*str = '\0';
	*line = str;
	if ((result = read_line(node, line, &str, tmp)) <= 0)
	{
		delete_buffer_fd(&list, node);
		if (result == -1)
		{
			*line = NULL;
			free(str);
		}
	}
	return (result);
}
