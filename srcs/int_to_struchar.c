/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_to_struchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:20:55 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/29 19:00:01 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char	*int_to_struchar(int n)
{
	unsigned char	*str;

	if ((str = (unsigned char *)malloc(2 * sizeof(unsigned char))))
	{
		str[0] = (unsigned char)n;
		str[1] = '\0';
	}
	return ((char *)str);
}
