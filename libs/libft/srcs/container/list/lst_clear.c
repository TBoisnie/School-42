#include "container/ft_list.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_clear(
	t_list * _lst,
	t_list_func_del _cleaner
)
{
	while (_lst)
		_lst = ft_lst_delete(_lst, _cleaner);

	return (_lst);
}
