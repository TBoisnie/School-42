/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:56:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:56:51 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*list_delete_first(t_list *list, void (*deleter)(void *))
{
	return (list_delete(list, list, deleter));
}
