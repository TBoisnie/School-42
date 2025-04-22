#include "libft.h"

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

t_void *
ft_mem_copy_safe(
	t_void const * _src,
	t_void * _dst,
	t_size _size
)
{
	t_byte const * src;
	t_byte * dst;

	if (_dst < _src)
	{
		src = _src;
		dst = _dst;

		while (_size--)
			*dst++ = *src++;
	}
	else
	{
		src = _src + (_size - 1);
		dst = _dst + (_size - 1);

		while (_size--)
			*dst-- = *src--;
	}

	return (_dst);
}
