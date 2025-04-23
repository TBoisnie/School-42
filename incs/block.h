#ifndef LIBFT_MALLOC_BLOCK_H
#define LIBFT_MALLOC_BLOCK_H

#include "libft/incs/ft_types.h"
#include "chunk.h"

// Define ----------------------------------------------------------------------
#define BLOCK_ALLOC_MIN (100)

// Macro -----------------------------------------------------------------------
#define BLOCK_IS_EMPTY(chunk) \
	(CHUNK_IS_FREE(chunk) && !CHUNK_HAS_PREV(chunk) && !CHUNK_HAS_NEXT(chunk))

// Struct ----------------------------------------------------------------------
typedef struct s_block
{
	struct s_block * prev;
	struct s_block * next;
	t_size size;
	t_chunk chunks;
} t_block;

// Function --------------------------------------------------------------------
t_size    _block_align_size(t_size _chunk_max_size, t_size _alloc_count);
t_block * _block_create(t_block * _prev, t_size _size);
t_block * _block_delete(t_block * _block);
t_chunk * _block_find_free_chunk(t_block * _block, t_size _size);

#endif
