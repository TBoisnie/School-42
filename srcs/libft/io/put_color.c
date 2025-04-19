/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 15:12:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:20:36 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	io_put_color(char *str, char *color, int fd)
{
	io_put_str(color, fd);
	io_put_str(str, fd);
	io_put_str(IO_C_NONE, fd);
}
