/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:57:38 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:57:40 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

t_list	*list_remove_last(t_list **list)
{
	if (list && *list)
		return (list_remove(list, list_get_last(*list)));
	return (NULL);
}
