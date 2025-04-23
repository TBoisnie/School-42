#include "zone.h"

t_chunk *
_zone_find_free_chunk(t_block * block, t_size size)
{
	// Note: assert(block != nullptr)

	t_chunk * chunk = nullptr;

	while (block)
	{
		chunk = _block_find_free_chunk(block, size);

		if (chunk)
		{
			break;
		}

		block = block->next;
	}

	return (chunk);
}
