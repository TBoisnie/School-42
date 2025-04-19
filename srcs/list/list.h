/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:48:02 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 12:51:31 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stddef.h>

typedef struct	s_list
{
	void			*content;

	struct s_list	*prev;
	struct s_list	*next;
}				t_list;

t_list			*list_new(void *content);

t_list			*list_delete(t_list *list, t_list *item, void(*deleter)(void*));
t_list			*list_delete_first(t_list *list, void(*deleter)(void*));
t_list			*list_delete_last(t_list *list, void(*deleter)(void*));

t_list			*list_remove(t_list **list, t_list *item);
t_list			*list_remove_first(t_list **list);
t_list			*list_remove_last(t_list **list);

t_list			*list_clear(t_list *list, void(*deleter)(void*));

t_list			*list_append(t_list *list, t_list *item);
t_list			*list_prepend(t_list *list, t_list *item);

t_list			*list_sort(t_list *list, int(*cmp)(void*, void*));

t_list			*list_get_last(t_list *list);

size_t			list_length(t_list *list);

#endif
