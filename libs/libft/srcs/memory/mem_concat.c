#include "libft.h"

// Function --------------------------------------------------------------------
t_void *
ft_mem_concat(
	t_void * _mem_1,
	t_void const * _mem_2,
	t_size _size_1,
	t_size _size_2
)
{
	return (ft_mem_copy(_mem_2, _mem_1 + _size_1, _size_2));
}
