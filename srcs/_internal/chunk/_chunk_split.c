#include "chunk.h"

t_chunk *
_chunk_split(t_chunk * _chunk, t_size _size)
{
	// Note: assert(_chunk != nullptr)
	// Note: assert(_size < CHUNK_GET_SIZE(_chunk))

	t_chunk chunk = *_chunk;

	_chunk_init(
		_chunk,
		_size,
		CHUNK_GET_FLAGS(&chunk) | CHUNK_HAS_NEXT_MASK
	);

	_chunk_init(
		_chunk_get_next(_chunk),
		CHUNK_GET_SIZE(&chunk) - _size - 2 * sizeof(t_chunk),
		CHUNK_GET_FLAGS(&chunk) | CHUNK_HAS_PREV_MASK | CHUNK_IS_FREE_MASK
	);

	return (_chunk);
}
