#include <stdlib.h>
#include "ft_memory.h"

// Function --------------------------------------------------------------------
t_void *
ft_mem_join(
	t_void const * _mem_1,
	t_void const * _mem_2,
	t_size _size_1,
	t_size _size_2
)
{
	t_byte * join = malloc(_size_1 + _size_2);

	if (!join)
		return (nullptr);

	ft_mem_copy(_mem_1, join, _size_1);
	ft_mem_concat(join, _mem_2, _size_1, _size_2);

	return (join);
}
