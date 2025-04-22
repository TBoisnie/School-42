#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_find(
	t_list const * _lst,
	t_list_func_find _matcher
)
{
	t_size index = 0;

	while (_lst)
	{
		if (_matcher(_lst->data, index++))
			return ((t_list *) _lst);

		_lst = _lst->next;
	}

	return (nullptr);
}

t_list *
ft_lst_rfind(
	t_list const * _lst,
	t_list_func_find _matcher
)
{
	t_size index = 0;

	_lst = ft_lst_back(_lst);
	while (_lst)
	{
		if (_matcher(_lst->data, index++))
			return ((t_list *) _lst);

		_lst = _lst->prev;
	}

	return (nullptr);
}
