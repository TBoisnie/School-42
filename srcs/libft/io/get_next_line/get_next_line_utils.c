/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:52:22 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 10:53:09 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

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
