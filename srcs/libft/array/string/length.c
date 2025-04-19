/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 18:26:56 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:22:24 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../array.h"

size_t	arr_str_length(char **arr)
{
	size_t	len;

	if (!arr)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}
