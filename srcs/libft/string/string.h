/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 07:24:17 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:25:42 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include <stddef.h>

char			*str_itoa(int n);
int				str_atoi(const char *str);

size_t			str_length(const char *str);

char			*str_chr(const char *str, char c);
int				str_cmp(const char *s1, const char *s2);
char			*str_dup(const char *str);
char			*str_join(const char *str_a, const char *str_b);
char			*str_replace(char *str, const char *find, const char *replace);
char			*str_sub(char const *str, unsigned int start, size_t length);
char			*str_trim(char const *str, char const *set);

char			*str_r_chr(const char *str, int c);

size_t			str_l_cpy(char *dst, const char *src, size_t size);
size_t			str_l_cat(char *dst, const char *src, size_t size);

char			*str_n_str(const char *str, const char *to_find, size_t length);
int				str_n_cmp(const char *s1, const char *s2, size_t n);

char			*str_mapi(char const *str, char (*f)(unsigned int, char));

char			**str_split(const char *str, char separator);

#endif
