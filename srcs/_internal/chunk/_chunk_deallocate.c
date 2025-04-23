#include "chunk.h"

t_chunk *
_chunk_deallocate(t_chunk * _chunk)
{
	// Note: assert(chunk != nullptr)

	CHUNK_SET_FREE(_chunk);

	t_chunk * prev = _chunk_get_prev(_chunk);
	if (prev && CHUNK_IS_FREE(prev))
	{
		_chunk = _chunk_merge(prev, _chunk);
	}

	t_chunk * next = _chunk_get_next(_chunk);
	if (next && CHUNK_IS_FREE(next))
	{
		_chunk = _chunk_merge(_chunk, next);
	}

	return (_chunk);
}
