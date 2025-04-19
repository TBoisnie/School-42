/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 09:45:34 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/15 09:24:49 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

# include <stddef.h>
# include <sys/types.h>

size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *str_a, const char *str_b);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *str);

ssize_t	ft_read(int fd, void *buffer, size_t length);
ssize_t	ft_write(int fd, const void *buffer, size_t length);

#endif