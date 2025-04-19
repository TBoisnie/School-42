/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 06:51:38 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:16:46 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "string.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		++s;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	size_t	s1_s2_len;
	int		i;

	i = 0;
	s1_s2_len = 0;
	while (s1[i++] != '\0')
		++s1_s2_len;
	i = 0;
	while (s2[i++] != '\0')
		++s1_s2_len;
	if ((join = (char *)malloc((s1_s2_len + 1) * sizeof(char))))
	{
		i = 0;
		while (*s1 != '\0')
			join[i++] = *s1++;
		while (*s2 != '\0')
			join[i++] = *s2++;
		join[i] = '\0';
	}
	return (join);
}

static int	read_line(t_buffer *node, char **line, char **str, char *tmp)
{
	ssize_t	c_read;
	char	*back_n;

	while ((node->position != 0 && (c_read = BUFFER_SIZE))
		|| (c_read = read(node->fd, node->buffer, BUFFER_SIZE)) > 0)
	{
		node->buffer[c_read] = '\0';
		if ((back_n = ft_strchr(&node->buffer[node->position], '\n')) != NULL)
			*back_n = '\0';
		tmp = *str;
		if (!(*str = ft_strjoin(*str, &node->buffer[node->position])))
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
	static t_buffer	node;
	char			*str;
	char			*tmp;
	int				result;

	tmp = NULL;
	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0
		|| !(str = (char *)malloc(sizeof(char))))
		return (-1);
	*str = '\0';
	*line = str;
	node.fd = fd;
	if ((result = read_line(&node, line, &str, tmp)) == -1)
	{
		*line = NULL;
		free(str);
	}
	return (result);
}
