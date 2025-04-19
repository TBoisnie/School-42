/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:48:57 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 22:32:38 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_INPUT_H
# define GET_INPUT_H

# include <stddef.h>

# define BUFFER_SIZE	64

typedef struct	s_buffer
{
	char	data[BUFFER_SIZE + 1];
	size_t	pos;
}				t_buffer;

int				get_input(char **line);

#endif
