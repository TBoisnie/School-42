#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_index(
	t_list const * _lst,
	t_size _index
)
{
	while (_lst && _index--)
		_lst = _lst->next;

	return ((t_list *) _lst);
}
