/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_length.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:41:02 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/09 01:54:37 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	str_length(const char *str)
{
	size_t	length;

	length = 0;
	if (!str)
		return (length);
	while (*str++ != '\0')
		length++;
	return (length);
}
