#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_iterate(
	t_list const * _lst,
	t_list_func_itr _callable
)
{
	t_size index = 0;

	t_list const * itr = _lst;
	while (itr)
	{
		_callable(itr->data, index++);

		itr = itr->next;
	}

	return ((t_list *) _lst);
}
