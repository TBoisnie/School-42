#include "container/ft_list.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_reverse(
	t_list * _lst
)
{
	if (!_lst)
		return (nullptr);

	if (!_lst->next)
		return (_lst);

	t_list * prev = _lst->prev;

	while (_lst)
	{
		prev = _lst->prev;
		_lst->prev = _lst->next;
		_lst->next = prev;

		_lst = _lst->prev;
	}

	return (ft_lst_front(prev));
}
