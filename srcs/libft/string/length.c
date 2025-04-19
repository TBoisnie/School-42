/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 07:45:20 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 21:39:07 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

size_t	str_length(const char *str)
{
	size_t	length;

	length = 0;
	while (str && *str++)
		++length;
	return (length);
}
