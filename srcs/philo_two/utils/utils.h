/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:29:13 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/11 01:56:39 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <sys/time.h>

void	sleep_ms(time_t t);

int		ret_error(int err_code, const char *str);

time_t	get_time_ms(struct timeval *time);

size_t	str_length(const char *str);
int		str_to_int(const char *str);

char	*time_to_str(char *str, time_t number);

void	*mem_copy(void *mem_dest, const void *mem_src, size_t length);

#endif
