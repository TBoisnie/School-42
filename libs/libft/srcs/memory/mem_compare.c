#include "libft.h"

// Function --------------------------------------------------------------------
t_int_8
ft_mem_compare(
	t_void const * _mem_1,
	t_void const * _mem_2,
	t_size _size
)
{
	t_byte const * byte_1 = _mem_1;
	t_byte const * byte_2 = _mem_2;

	while (_size--)
	{
		if (*byte_1++ != *byte_2++)
			return (byte_1[-1] < byte_2[-1] ? -1 : 1);
	}

	return (0);
}
