#include "ft_memory.h"

// Function --------------------------------------------------------------------
t_void *
ft_mem_fill(
	t_void * _mem,
	t_byte const _value,
	t_size _size
)
{
	t_byte * byte = _mem;

	while (_size--)
		*byte++ = _value;

	return (_mem);
}
