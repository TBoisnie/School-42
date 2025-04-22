#include "ft_memory.h"

// Function --------------------------------------------------------------------
t_void *
ft_mem_copy(
	t_void const * _src,
	t_void * _dst,
	t_size _size
)
{
	t_byte const * src = _src;
	t_byte * dst = _dst;

	while (_size--)
		*dst++ = *src++;

	return (_dst);
}
