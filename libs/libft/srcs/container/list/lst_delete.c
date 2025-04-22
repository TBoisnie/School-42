#include <stdlib.h>
#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_delete(
	t_list * _node,
	t_list_func_del _cleaner
)
{
	if (!_node)
		return (nullptr);

	if (_node->prev)
		_node->prev->next = _node->next;
	if (_node->next)
		_node->next->prev = _node->prev;

	t_list * next = _node->next;

	if (_cleaner)
		_cleaner(_node->data);

	free(_node);

	return (next);
}
