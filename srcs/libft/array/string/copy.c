/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 18:26:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:25:24 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../string/string.h"
#include "../array.h"

char	**arr_str_copy(char **arr)
{
	size_t	i;
	size_t	arr_len;
	char	**copy;

	arr_len = arr_str_length(arr);
	if (!(copy = arr_str_new(arr_len)))
		return (NULL);
	i = 0;
	while (arr[i])
	{
		if (!(copy[i] = str_dup(arr[i])))
			break ;
		++i;
	}
	copy[i] = NULL;
	if (i != arr_len)
		copy = arr_str_clear(copy);
	return (copy);
}
