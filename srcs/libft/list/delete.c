/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:56:31 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:56:34 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

t_list	*list_delete(t_list *list, t_list *item, void (*deleter)(void *))
{
	t_list	*current;

	if (list == NULL || item == NULL)
		return (list);
	current = list;
	while (current)
	{
		if (current == item)
		{
			if (deleter)
				deleter(current->content);
			if (!current->prev)
				list = current->next;
			else
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(current);
			break ;
		}
		current = current->next;
	}
	return (list);
}
