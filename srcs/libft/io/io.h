/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:18:43 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:22:45 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# define IO_IN	0
# define IO_OUT	1
# define IO_ERR 2

# define IO_C_NONE "\e[0m"
# define IO_C_RED "\e[31m"
# define IO_C_GREEN "\e[32m"
# define IO_C_ORANGE "\e[33m"
# define IO_C_GREY "\e[90m"
# define IO_C_BLUE "\e[94m"

void	io_put_char(char c, int fd);
void	io_put_endl(char *str, int fd);
void	io_put_nbr(int n, int fd);
void	io_put_str(char *str, int fd);
void	io_put_err(char *str);
void	io_put_color(char *str, char *color, int fd);

#endif
