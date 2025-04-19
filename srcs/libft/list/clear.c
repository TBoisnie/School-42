/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:55:50 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:56:09 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_clear(t_list *list, void (*deleter)(void *))
{
	while (list)
		list = list_delete_first(list, deleter);
	return (list);
}
