/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:35:50 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 13:15:53 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# define BUFFER_SIZE 64

# include <stddef.h>

typedef struct	s_buffer
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
	size_t	position;
}				t_buffer;

size_t			str_length(char *str);

char			*str_from_int_base(int number, char *base);
char			*str_to_int(char *str, int *result);

char			*str_join(char *str_a, char *str_b);
char			*str_join_char(char *str, char c);

int				str_contains(char *str, char c);

int				ft_isspace(char c);

int				get_next_line(const int fd, char **line);

#endif
