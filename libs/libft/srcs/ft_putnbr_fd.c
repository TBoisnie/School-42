/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:30:02 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/08 16:37:38 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	safe_n;

	safe_n = (long)n;
	if (safe_n < 0)
	{
		safe_n *= -1;
		ft_putchar_fd('-', fd);
	}
	if (safe_n / 10 > 0)
		ft_putnbr_fd(safe_n / 10, fd);
	ft_putchar_fd('0' + (safe_n % 10), fd);
}
