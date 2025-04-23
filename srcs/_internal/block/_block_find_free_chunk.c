#include "block.h"

t_chunk *
_block_find_free_chunk(t_block * _block, t_size _size)
{
	// Note: assert(block != nullptr)

	t_chunk * chunk = &_block->chunks;

	while (chunk)
	{
		if (CHUNK_IS_FREE(chunk) && CHUNK_GET_SIZE(chunk) >= _size)
		{
			break;
		}

		chunk = _chunk_get_next(chunk);
	}

	return (chunk);
}
