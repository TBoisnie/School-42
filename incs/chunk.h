#ifndef LIBFT_MALLOC_CHUNK_H
#define LIBFT_MALLOC_CHUNK_H

#include "libft/incs/ft_math.h"
#include "libft/incs/ft_types.h"

// Define ----------------------------------------------------------------------
// Align size to a multiple of 8, meaning the 3 least significant bits are 0
#define CHUNK_ALIGN_MASK    (1 << 3)

#define CHUNK_HAS_PREV_MASK (1 << 2) // Use 3rd least significant bit as flag
#define CHUNK_HAS_NEXT_MASK (1 << 1) // Use 2nd least significant bit as flag
#define CHUNK_IS_FREE_MASK  (1 << 0) // Use 1st least significant bit as flag

// Combine all flags mask for easier use
#define CHUNK_GET_FLAGS_MASK (CHUNK_HAS_PREV_MASK | CHUNK_HAS_NEXT_MASK | CHUNK_IS_FREE_MASK)
// Use most significant bits as size
#define CHUNK_GET_SIZE_MASK  (~CHUNK_GET_FLAGS_MASK)

// Macro -----------------------------------------------------------------------
#define CHUNK_ALIGN_SIZE(size)  (FT_MATH_ROUND_POWER_2(size, CHUNK_ALIGN_MASK))

#define CHUNK_HAS_PREV(chunk)   (((t_chunk *)chunk)->metadata & CHUNK_HAS_PREV_MASK)
#define CHUNK_HAS_NEXT(chunk)   (((t_chunk *)chunk)->metadata & CHUNK_HAS_NEXT_MASK)
#define CHUNK_IS_FREE(chunk)    (((t_chunk *)chunk)->metadata & CHUNK_IS_FREE_MASK)

#define CHUNK_SET_PREV(chunk)   (((t_chunk *)chunk)->metadata |= CHUNK_HAS_PREV_MASK)
#define CHUNK_SET_NEXT(chunk)   (((t_chunk *)chunk)->metadata |= CHUNK_HAS_NEXT_MASK)
#define CHUNK_SET_FREE(chunk)   (((t_chunk *)chunk)->metadata |= CHUNK_IS_FREE_MASK)

#define CHUNK_UNSET_PREV(chunk) (((t_chunk *)chunk)->metadata &= ~CHUNK_HAS_PREV_MASK)
#define CHUNK_UNSET_NEXT(chunk) (((t_chunk *)chunk)->metadata &= ~CHUNK_HAS_NEXT_MASK)
#define CHUNK_UNSET_FREE(chunk) (((t_chunk *)chunk)->metadata &= ~CHUNK_IS_FREE_MASK)

#define CHUNK_GET_FLAGS(chunk)  (((t_chunk *)chunk)->metadata & CHUNK_GET_FLAGS_MASK)
#define CHUNK_GET_SIZE(chunk)   (((t_chunk *)chunk)->metadata & CHUNK_GET_SIZE_MASK)

#define CHUNK_SET_SIZE(chunk, size) \
	(((t_chunk *)chunk)->metadata = size | CHUNK_GET_FLAGS(chunk))

#define CHUNK_SET_FLAGS(chunk, flags) \
	(((t_chunk *)chunk)->metadata = flags | CHUNK_GET_SIZE(chunk))

// Struct ----------------------------------------------------------------------
typedef struct
{
	t_size metadata; // 4 bytes * 2 = CHUNK_ALIGN_MASK
	// t_byte payload[];
	// t_byte padding[];
	// t_size metadata;
} t_chunk;

// Function --------------------------------------------------------------------
t_chunk * _chunk_allocate(t_chunk * _chunk, t_size _size);
t_chunk * _chunk_deallocate(t_chunk * _chunk);
t_chunk * _chunk_get_next(t_chunk * _chunk);
t_chunk * _chunk_get_prev(t_chunk * _chunk);
t_chunk * _chunk_init(t_chunk * _chunk, t_size _size, t_size _flags);
t_chunk * _chunk_merge(t_chunk * _left, t_chunk * _right);
t_chunk * _chunk_split(t_chunk * _chunk, t_size _size);

#endif
