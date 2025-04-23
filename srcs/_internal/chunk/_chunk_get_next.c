#include "chunk.h"

t_chunk *
_chunk_get_next(t_chunk * _chunk)
{
	// Note: assert(chunk != nullptr)

	if (!CHUNK_HAS_NEXT(_chunk))
	{
		return (nullptr);
	}

	t_byte * next = (t_byte *)_chunk;
	next += CHUNK_GET_SIZE(next) + 2 * sizeof(t_chunk);

	return ((t_chunk*)next);
}
