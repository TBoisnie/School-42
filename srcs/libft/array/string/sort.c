/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 19:11:51 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:21:49 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../array.h"

void	arr_str_sort(char **arr, int (*cmp)(const char *, const char *))
{
	char	*tmp;
	int		a;
	int		b;

	if (!arr)
		return ;
	a = 0;
	b = 1;
	while (arr[a] && arr[b])
	{
		if (cmp(arr[a], arr[b]) > 0)
		{
			tmp = arr[a];
			arr[a] = arr[b];
			arr[b] = tmp;
			a = -1;
			b = 0;
		}
		a++;
		b++;
	}
}
