/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepend.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:27:15 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 12:45:41 by tboisnie         ###   ########.fr       */
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
