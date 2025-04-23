#include "container/ft_list.h"

// Function --------------------------------------------------------------------
t_size
ft_lst_size(
	t_list const * _lst
)
{
	t_size size;

	for (size = 0; _lst != nullptr; size++)
		_lst = _lst->next;

	return (size);
}
