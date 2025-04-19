/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 19:13:39 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 12:43:26 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_clear(t_list *list, void (*deleter)(void *))
{
	while (list)
		list = list_delete_first(list, deleter);
	return (list);
}
