/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 19:26:38 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:18:34 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../array.h"

char	**arr_str_clear(char **arr)
{
	size_t	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
}
