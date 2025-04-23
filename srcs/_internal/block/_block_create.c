#include <sys/mman.h>
#include "block.h"

t_block *
_block_create(t_block * _prev, t_size _size)
{
	t_void * map = mmap(nullptr, _size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);

	if (map == MAP_FAILED)
	{
		return (nullptr);
	}

	t_block * block = map;
	block->prev = _prev;
	block->next = nullptr;
	block->size = _size;

	_chunk_init(&block->chunks, _size - sizeof(t_block) - sizeof(t_chunk), CHUNK_IS_FREE_MASK);

	if (_prev)
	{
		_prev->next = block;
	}

	return (block);
}
