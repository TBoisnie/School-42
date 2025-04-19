/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 19:15:29 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:17:42 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

# include <stddef.h>

char	**arr_str_new(size_t size);
char	**arr_str_clear(char **arr);
char	**arr_str_copy(char **arr);
char	**arr_str_append(char **arr, char *str);
size_t	arr_str_length(char **arr);
void	arr_str_sort(char **arr, int (*cmp)(const char *, const char *));

#endif
