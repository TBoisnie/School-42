/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:41:48 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:20:03 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	io_put_nbr(int n, int fd)
{
	long	safe_n;

	safe_n = (long)n;
	if (safe_n < 0)
	{
		safe_n *= -1;
		io_put_char('-', fd);
	}
	if (safe_n / 10 > 0)
		io_put_nbr(safe_n / 10, fd);
	io_put_char('0' + (safe_n % 10), fd);
}
