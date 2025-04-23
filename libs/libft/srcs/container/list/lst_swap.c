#include "container/ft_list.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_swap(
	t_list * _node_1,
	t_list * _node_2
)
{
	t_void * tmp = _node_1->data;

	_node_1->data = _node_2->data;
	_node_2->data = tmp;

	return (_node_1);
}
