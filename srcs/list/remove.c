/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 17:07:54 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 12:46:05 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

t_list	*list_remove(t_list **list, t_list *item)
{
	if (!list || !item)
		return (NULL);
	if (item->prev)
		item->prev->next = item->next;
	else
		*list = item->next;
	if (item->next)
		item->next->prev = item->prev;
	return (item);
}
