/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:48:57 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/04 23:37:37 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *b, size_t len)
{
	unsigned char	*str;

	str = (unsigned char *)b;
	while (len--)
	{
		*str++ = (unsigned char)'\0';
	}
}
