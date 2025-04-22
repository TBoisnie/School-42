#include "libft.h"

// Function --------------------------------------------------------------------
t_void *
ft_mem_reverse(
	t_void * _mem,
	t_size _size
)
{
	t_byte * left = _mem;
	t_byte * right = _mem + _size - 1;

	t_byte temp;
	while (left < right)
	{
		temp = *left;
		*left++ = *right;
		*right-- = temp;
	}

	return (_mem);
}
