/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:57:03 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:57:04 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_get_last(t_list *list)
{
	while (list)
	{
		if (!list->next)
			break ;
		list = list->next;
	}
	return (list);
}
