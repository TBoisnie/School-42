/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:56:25 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:56:48 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_delete_last(t_list *list, void (*deleter)(void *))
{
	return (list_delete(list, list_get_last(list), deleter));
}
