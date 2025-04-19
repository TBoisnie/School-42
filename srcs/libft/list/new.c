/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:57:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:57:21 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

t_list	*list_new(void *content)
{
	t_list	*item;

	if (!(item = malloc(sizeof(t_list))))
		return (NULL);
	item->content = content;
	item->prev = NULL;
	item->next = NULL;
	return (item);
}
