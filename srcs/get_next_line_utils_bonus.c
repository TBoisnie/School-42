/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 06:42:22 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/27 13:50:01 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line_bonus.h"

t_buffer_list	*create_buffer_fd(const int fd)
{
	t_buffer_list	*node;

	if ((node = (t_buffer_list *)malloc(sizeof(t_buffer_list))))
	{
		node->fd = fd;
		node->buffer[0] = '\0';
		node->buffer[BUFFER_SIZE] = '\0';
		node->position = 0;
		node->prev = NULL;
		node->next = NULL;
	}
	return (node);
}

t_buffer_list	*get_buffer_fd(t_buffer_list **list, const int fd)
{
	t_buffer_list	*node;

	node = *list;
	if (node == NULL)
	{
		node = create_buffer_fd(fd);
		*list = node;
	}
	else
		while (node != NULL)
		{
			if (node->fd == fd)
				return (node);
			else if (node->next == NULL)
			{
				node->next = create_buffer_fd(fd);
				if (node->next != NULL)
					node->next->prev = node;
				return (node->next);
			}
			else
				node = node->next;
		}
	return (node);
}

void			delete_buffer_fd(t_buffer_list **list, t_buffer_list *node)
{
	if (node != NULL)
	{
		if (node->prev == NULL)
			*list = node->next;
		else
			node->prev->next = node->next;
		free(node);
	}
}

char			*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		++s;
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return (NULL);
}

char			*ft_strjoin(const char *s1, const char *s2)
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
