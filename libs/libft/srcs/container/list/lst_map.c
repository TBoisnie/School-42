#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_map(
	t_list * _lst,
	t_list_func_map _callable
)
{
	t_size index = 0;

	t_list * itr = _lst;
	while (itr)
	{
		itr->data = _callable(itr->data, index++);

		itr = itr->next;
	}

	return (_lst);
}
