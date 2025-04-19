/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 06:57:50 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/27 06:57:51 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "list.h"

static void		split(t_list *list, t_list **a, t_list **b)
{
	t_list	*fast;
	t_list	*slow;

	slow = list;
	fast = list->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = list;
	*b = slow->next;
	slow->next = NULL;
}

static t_list	*merge(t_list *a, t_list *b, int (*cmp)(void *, void*))
{
	t_list	*result;

	if (!a)
		return (b);
	if (!b)
		return (a);
	if (cmp(a->content, b->content) <= 0)
	{
		result = a;
		result->next = merge(a->next, b, cmp);
		if (result->next)
			result->next->prev = result;
	}
	else
	{
		result = b;
		result->next = merge(a, b->next, cmp);
		if (result->next)
			result->next->prev = result;
	}
	return (result);
}

t_list			*list_sort(t_list *list, int (*cmp)(void *, void*))
{
	t_list	*head;
	t_list	*a;
	t_list	*b;

	if (!list || !list->next)
		return (list);
	head = list;
	split(head, &a, &b);
	a = list_sort(a, cmp);
	b = list_sort(b, cmp);
	return (merge(a, b, cmp));
}
