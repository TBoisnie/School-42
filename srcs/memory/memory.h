/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 10:37:35 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/10 18:00:40 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stddef.h>

void	*mem_bzero(void *mem, size_t length);
void	*mem_copy(void *mem_dest, const void *mem_src, size_t length);
void	*mem_set(void *mem, int c, size_t length);

#endif
