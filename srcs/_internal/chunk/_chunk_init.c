#include "chunk.h"

t_chunk *
_chunk_init(t_chunk * _chunk, t_size _size, t_size _flags)
{
	// Note: assert(addr != nullptr)

	CHUNK_SET_SIZE(_chunk, _size);
	CHUNK_SET_FLAGS(_chunk, _flags);

	t_byte * tail = (t_byte *)_chunk;
	tail += sizeof(t_chunk) + _size;

	((t_chunk *)tail)->metadata = _chunk->metadata;

	return (_chunk);
}
