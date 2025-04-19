/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 20:03:26 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 12:47:48 by tboisnie         ###   ########.fr       */
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
