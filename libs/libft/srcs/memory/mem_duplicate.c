#include <stdlib.h>
#include "libft.h"

// Function --------------------------------------------------------------------
t_void *
ft_mem_duplicate(
	t_void const * _mem,
	t_size _size
)
{
	t_byte * copy = malloc(_size);

	if (!copy)
		return (nullptr);

	return (ft_mem_copy(_mem, copy, _size));
};
