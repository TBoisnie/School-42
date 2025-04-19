/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 16:53:59 by tboisnie          #+#    #+#             */
/*   Updated: 2019/11/14 18:59:48 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (alst != NULL)
	{
		last = ft_lstlast(*alst);
		if (last == NULL)
			*alst = new;
		else
			last->next = new;
	}
}
