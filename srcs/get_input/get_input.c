/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:16:18 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 22:33:51 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/io/io.h"
#include "libft/string/string.h"
#include "get_input.h"

extern int g_stop;

static void	set_backn(t_buffer *buf, char **p_back_n)
{
	if ((*p_back_n = str_chr(&buf->data[buf->pos], '\n')) != NULL)
		**p_back_n = '\0';
}

static int	read_line(t_buffer *buf, char **line, char **str, char *tmp)
{
	ssize_t	c_read;
	char	*back_n;

	while ((buf->pos != 0 && (c_read = BUFFER_SIZE))
		|| (c_read = read(IO_IN, buf->data, BUFFER_SIZE)) > 0
		|| (c_read == 0 && **line))
	{
		buf->data[c_read] = '\0';
		set_backn(buf, &back_n);
		tmp = *str;
		if (!(*str = str_join(!g_stop ? *str : NULL, &buf->data[buf->pos])))
		{
			free(tmp);
			return (-1);
		}
		*line = *str;
		free(tmp);
		if (back_n != NULL)
		{
			buf->pos = (int)(back_n - buf->data + 1);
			return (1);
		}
		buf->pos = 0;
	}
	return ((int)c_read);
}

int			get_input(char **line)
{
	static t_buffer	buf;
	char			*str;
	char			*tmp;
	int				result;

	tmp = NULL;
	if (line == NULL || BUFFER_SIZE <= 0
		|| !(str = malloc(sizeof(char))))
		return (-1);
	*str = '\0';
	*line = str;
	if ((result = read_line(&buf, line, &str, tmp)) == -1)
	{
		*line = NULL;
		free(str);
	}
	return (result);
}
