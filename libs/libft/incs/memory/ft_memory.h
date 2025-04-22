#ifndef LIBFT_MEMORY_H
#define LIBFT_MEMORY_H

#include "../core/ft_types.h"

// Macro -----------------------------------------------------------------------
#define FT_MEM_BIT_SET(m, b)     (m |= b)
#define FT_MEM_BIT_UNSET(m, b)   (m &= ~(b))
#define FT_MEM_BIT_TOGGLE(m, b)  (m ^= b)
#define FT_MEM_BIT_CLEAR(m)      (m ^= m)
#define FT_MEM_BIT_ISSET(m, b)   ((m) & (b))

// Alias -----------------------------------------------------------------------
#define ft_mem_move  ft_mem_copy_safe

// Function --------------------------------------------------------------------
/**
 * Compare 2 memory blocks, byte by byte.
 *
 * @param _mem_1: First memory block
 * @param _mem_2: Second memory block
 * @param _size: Size of blocks to compare
 *
 * @return `0` if the blocks are identical, `-1` if the first byte to mismatch
 * is inferior in _mem_1 than in _mem_2, `1` otherwise
**/
t_int_8 ft_mem_compare(t_void const * _mem_1, t_void const * _mem_2, t_size _size);

/**
 * Concatenate 2 memory blocks.
 *
 * @param _mem_1: First memory block
 * @param _mem_2: Second memory block
 * @param _size_1: Size of the first memory block
 * @param _size_2: Size of the second memory block
 *
 * @return Concatenated memory blocks
 *
 * @warning `_mem_1` must be large enough to contains the concatenation
**/
t_void * ft_mem_concat(t_void * _mem_1, t_void const * _mem_2, t_size _size_1, t_size _size_2);

/**
 * Copy a memory block into another one (overlap unsafe).
 *
 * @param _src: Memory block to copy from
 * @param _dst: Memory block to copy to
 * @param _size: Size of the memory block to copy
 *
 * @return Copied memory block
 *
 * @warning No overlap check is performed
**/
t_void * ft_mem_copy(t_void const * _src, t_void * _dst, t_size _size);

/**
 * Copy a memory block into another one (overlap safe).
 *
 * @param _src: Memory block to copy from
 * @param _dst: Memory block to copy to
 * @param _size: Size of memory block to copy
 *
 * @return Copied memory block
**/
t_void * ft_mem_copy_safe(t_void const * _src, t_void * _dst, t_size _size);

/**
 * Copy a memory block into a new allocated one.
 *
 * @param _mem: Memory block to duplicate
 * @param _size: Size of the memory block
 *
 * @return Newly allocated memory block
 *
 * @exception If allocation failed, `nullptr` is returned
**/
t_void * ft_mem_duplicate(t_void const * _mem, t_size _size);

/**
 * Concatenate 2 memory blocks into a new allocated one.
 *
 * @param _mem_1: First memory block
 * @param _mem_2: Second memory block
 * @param _size_1: Size of the first memory block
 * @param _size_2: Size of the seoncd memory block
 *
 * @return Newly allocated memory block
 *
 * @exception If allocation failed, `nullptr` is returned
**/
t_void * ft_mem_join(t_void const * _mem_1, t_void const * _mem_2, t_size _size_1, t_size _size_2);

/**
 * Fill a memory block with value.
 *
 * @param _mem: Memory block to fill
 * @param _value: Value to fill with
 * @param _size: Size of the memory block to fill
 *
 * @return Filled memory block
**/
t_void * ft_mem_fill(t_void * _mem, t_byte _value, t_size _size);

/**
 * Fill a memory block with 0.
 *
 * @param _mem: Memory block
 * @param _size: Size of the memory block
 *
 * @return Filled memory block
**/
t_void * ft_mem_clear(t_void * _mem, t_size _size);

/**
 * Reverse a memory block, byte by byte.
 *
 * @param _mem: Memory block to reverse
 * @param _size: Size of the memory block
 *
 * @return Reversed memory block
**/
t_void * ft_mem_reverse(t_void * _mem, t_size _size);

/**
 * Calculate the checksum (16 bits) of a memory block.
 *
 * @param _mem: Memory block
 * @param _size: Size of the memory block
 *
 * @return Calculated checksum
**/
t_uint_16 ft_mem_checksum_16(t_void const * _mem, t_size _size);

/**
 * Convert 2 hex characters to byte.
 *
 * @param _hex: Hex characters to convert
 *
 * @return Byte representation
 */
t_byte ft_mem_hex_to_byte(t_char const _hex[2]);

#endif
