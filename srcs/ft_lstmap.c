/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:48:15 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/14 20:51:28 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_current;

	if (lst == NULL || f == NULL || *f == NULL
		|| !(new_current = ft_lstnew(f(lst->content))))
		return (NULL);
	new_lst = new_current;
	lst = lst->next;
	while (lst != NULL)
	{
		if (!(new_current->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		lst = lst->next;
		new_current = new_current->next;
	}
	return (new_lst);
}
