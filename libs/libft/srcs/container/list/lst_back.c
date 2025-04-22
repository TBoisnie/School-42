#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_back(
	t_list const * _lst
)
{
	if (!_lst)
		return (nullptr);

	while (_lst->next)
		_lst = _lst->next;

	return ((t_list *)_lst);
}
