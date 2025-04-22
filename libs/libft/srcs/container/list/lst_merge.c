#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_merge(
	t_list * _lst_1,
	t_list * _lst_2
)
{
	if (!_lst_1)
		return (_lst_2);

	if (_lst_2)
	{
		t_list * back = ft_lst_back(_lst_1);

		back->next = _lst_2;
		_lst_2->prev = back;
	}

	return (_lst_1);
}
