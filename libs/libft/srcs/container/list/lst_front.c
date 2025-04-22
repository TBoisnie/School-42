#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_front(
	t_list const * _lst
)
{
	if (!_lst)
		return (nullptr);

	while (_lst->prev)
		_lst = _lst->prev;

	return ((t_list *)_lst);
}
