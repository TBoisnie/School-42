/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:08:43 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/27 13:49:32 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>

typedef struct	s_buffer_list
{
	int						fd;
	char					buffer[BUFFER_SIZE + 1];
	size_t					position;
	struct s_buffer_list	*prev;
	struct s_buffer_list	*next;
}				t_buffer_list;

t_buffer_list	*create_buffer_fd(const int fd);
void			delete_buffer_fd(t_buffer_list **list, t_buffer_list *node);
t_buffer_list	*get_buffer_fd(t_buffer_list **list, const int fd);

char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(const char *s1, const char *s2);

int				get_next_line(const int fd, char **line);

#endif
