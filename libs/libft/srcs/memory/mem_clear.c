#include "ft_memory.h"

// Function --------------------------------------------------------------------
t_void *
ft_mem_clear(
	t_void * _mem,
	t_size _size
)
{
	return (ft_mem_fill(_mem, 0, _size));
}
