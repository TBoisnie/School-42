/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:04:39 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 12:44:44 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

size_t	list_length(t_list *list)
{
	size_t	length;

	length = 0;
	while (list)
	{
		list = list->next;
		length++;
	}
	return (length);
}
