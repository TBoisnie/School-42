/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:21:03 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 12:42:36 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_append(t_list *list, t_list *item)
{
	t_list	*last;

	if (!(last = list_get_last(list)))
		return (item);
	last->next = item;
	if (item)
		item->prev = last;
	return (list);
}
