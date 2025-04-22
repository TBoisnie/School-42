#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_push_back(
	t_list * _lst,
	t_void * _data
)
{
	t_list * item = ft_lst_new(_data);

	if (!item)
		return (nullptr);

	t_list * back = ft_lst_back(_lst);

	if (back)
	{
		back->next = item;
		item->prev = back;
	}

	return (item);
}

t_list *
ft_lst_push_front(
	t_list * _lst,
	t_void * _data
)
{
	t_list * item = ft_lst_new(_data);

	if (!item)
		return (nullptr);

	t_list * front = ft_lst_front(_lst);

	if (front)
	{
		item->next = front;
		front->prev = item;
	}

	return (item);
}
