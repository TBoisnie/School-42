#include "chunk.h"

t_chunk *
_chunk_allocate(t_chunk * _chunk, t_size _size)
{
	// Note: assert(_chunk != nullptr)
	// Note: assert(CHUNK_IS_FREE(_chunk))
	// Note: assert(CHUNK_GET_SIZE(_size) <= size)

	CHUNK_UNSET_FREE(_chunk);

	if (_size == CHUNK_GET_SIZE(_chunk))
	{
		return (_chunk);
	}

	_chunk_split(_chunk, _size);

	return (_chunk);
}
