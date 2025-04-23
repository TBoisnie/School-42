#include "chunk.h"

t_chunk *
_chunk_get_prev(t_chunk * _chunk)
{
	// Note: assert(chunk != nullptr)

	if (!CHUNK_HAS_PREV(_chunk))
	{
		return (nullptr);
	}

	t_byte * prev = (t_byte *)_chunk - sizeof(t_chunk);
	prev -= CHUNK_GET_SIZE(prev) - sizeof(t_chunk);

	return ((t_chunk *)prev);
}
