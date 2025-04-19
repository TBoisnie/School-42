/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 07:03:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 21:24:04 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <stddef.h>

void	*mem_bzero(void *mem, size_t length);

void	*mem_copy(void *mem_dest, const void *mem_src, size_t length);
void	*mem_c_cpy(void *dst, const void *src, int c, size_t n);

void	*mem_calloc(size_t length, size_t size);

void	*mem_move(void *mem_dst, const void *mem_src, size_t length);
void	*mem_set(void *mem, int c, size_t length);
void	*mem_chr(const void *mem, int c, size_t length);

int		mem_cmp(const void *mem_a, const void *mem_b, size_t length);

#endif
