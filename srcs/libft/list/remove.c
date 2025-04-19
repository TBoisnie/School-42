/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:57:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:57:45 by tboisnie         ###   ########.fr       */
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
