#include "chunk.h"

t_chunk *
_chunk_merge(t_chunk * _left, t_chunk * _right)
{
	// Note: assert(_left != nullptr)
	// Note: assert(_right != nullptr)
	// Note: assert(_left < _right)

	t_size size =
		CHUNK_GET_SIZE(_left) + CHUNK_GET_SIZE(_right) + 2 * sizeof(t_chunk);
	t_size flags =
		(CHUNK_HAS_PREV(_left)  * CHUNK_HAS_PREV_MASK) |
		(CHUNK_HAS_NEXT(_right) * CHUNK_HAS_NEXT_MASK) |
		(CHUNK_IS_FREE(_left)   * CHUNK_IS_FREE_MASK);

	return (_chunk_init(_left, size, flags));
}
