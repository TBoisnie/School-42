#include <sys/mman.h>
#include "block.h"

t_block *
_block_delete(t_block * _block)
{
	// Note: assert(block != nullptr)

	t_block * prev = _block->prev;
	t_block * next = _block->next;

	t_int map = munmap(_block, _block->size);

	if (map != 0)
	{
		// Todo: Trigger error (munmap failed)
		return (_block);
	}

	_block = nullptr;

	if (next)
	{
		next->prev = prev;
		_block = next;
	}

	if (prev)
	{
		prev->next = next;
		_block = prev;
	}

	while (_block && _block->prev)
	{
		_block = _block->prev;
	}

	return (_block);
}
