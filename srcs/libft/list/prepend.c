/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:57:26 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:57:27 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_prepend(t_list *list, t_list *item)
{
	if (item)
	{
		item->next = list;
		if (list)
			list->prev = item;
	}
	else
		item = list;
	return (item);
}
