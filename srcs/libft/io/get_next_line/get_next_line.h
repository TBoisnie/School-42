/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:48:57 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:24:59 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

# define BUFFER_SIZE	64

typedef struct	s_buffer_list
{
	int						fd;
	char					buffer[BUFFER_SIZE + 1];
	size_t					position;
	struct s_buffer_list	*prev;
	struct s_buffer_list	*next;
}				t_buffer_list;

t_buffer_list	*get_buffer_fd(t_buffer_list **list, const int fd);
t_buffer_list	*create_buffer_fd(const int fd);
void			delete_buffer_fd(t_buffer_list **list, t_buffer_list *node);

int				get_next_line(const int fd, char **line);

#endif
