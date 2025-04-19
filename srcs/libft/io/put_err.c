/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:38:39 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:20:43 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	io_put_err(char *str)
{
	io_put_str(IO_C_RED, IO_ERR);
	io_put_str(str, IO_ERR);
	io_put_endl(IO_C_NONE, IO_ERR);
}
