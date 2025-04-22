#include "libft.h"

// Function --------------------------------------------------------------------
t_uint_16
ft_mem_checksum_16(
	t_void const * _mem,
	t_size _size
)
{
	t_uint_32 checksum = 0;
	t_uint_16 const * chunk = _mem;

	for (/**/; _size > 1; _size -= 2)
		checksum += *chunk++;

	if (_size == 1)
		checksum += * (t_uint_8 *) chunk;

	checksum  = (checksum >> 16) + (checksum & 0xFFFF);
	checksum += (checksum >> 16);
	checksum  = ~checksum;

	return ((t_uint_16) checksum);
}
