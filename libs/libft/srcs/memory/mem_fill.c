#include "libft.h"

// Function --------------------------------------------------------------------
t_void *
ft_mem_fill(
	t_void * _mem,
	t_byte _value,
	t_size _size
)
{
	t_byte * byte = _mem;

	while (_size--)
		*byte++ = _value;

	return (_mem);
}

t_void *
ft_mem_clear(
	t_void * _mem,
	t_size _size
)
{
	return (ft_mem_fill(_mem, 0, _size));
}
