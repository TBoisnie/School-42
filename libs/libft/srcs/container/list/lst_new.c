#include <stdlib.h>
#include "libft.h"

// Function --------------------------------------------------------------------
t_list *
ft_lst_new(
	t_void * _data
)
{
	t_list * item = malloc(sizeof(t_list));

	if (!item)
		return (nullptr);

	item->data = _data;
	item->prev = nullptr;
	item->next = nullptr;

	return (item);
}
