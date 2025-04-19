/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 19:11:51 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:21:49 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../array.h"

char	**arr_str_append(char **arr, char *str)
{
	size_t	size;
	char	**arr_new;

	size = arr_str_length(arr);
	if (!(arr_new = arr_str_new(size + 1)))
		return (arr);
	arr_new[size + 1] = NULL;
	arr_new[size] = str;
	while (size--)
		arr_new[size] = arr[size];
	free(arr);
	return (arr_new);
}
