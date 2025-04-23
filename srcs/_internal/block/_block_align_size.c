#include <unistd.h>
#include "libft/incs/ft_math.h"
#include "block.h"

t_size
_block_align_size(t_size _chunk_max_size, t_size _alloc_count)
{
	// Note: assert(_alloc_count > 0)

	t_size size = sizeof(t_block) + sizeof(t_chunk) + _chunk_max_size;

	if (_alloc_count > 1)
	{
		size += (_alloc_count - 1) * (_chunk_max_size + 2 * sizeof(t_chunk));
	}

	return (FT_MATH_ROUND_POWER_2(size, getpagesize()));
}
