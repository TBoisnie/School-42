#ifndef LIBFT_MEMORY_H
#define LIBFT_MEMORY_H

#include "ft_types.h"

// Macro -----------------------------------------------------------------------
#define FT_MEM_BIT_SET(m, b)    (m |= b)
#define FT_MEM_BIT_UNSET(m, b)  (m &= ~(b))
#define FT_MEM_BIT_TOGGLE(m, b) (m ^= b)
#define FT_MEM_BIT_CLEAR(m)     (m ^= m)
#define FT_MEM_BIT_ISSET(m, b)  ((m) & (b))

// Function --------------------------------------------------------------------
t_void * ft_mem_clear(t_void * _mem, t_size _size);
t_int    ft_mem_compare(t_void const * _mem_1, t_void const * _mem_2, t_size _size);
t_void * ft_mem_concat(t_void * _mem_1, t_void const * _mem_2, t_size _size_1, t_size _size_2);
t_void * ft_mem_copy(t_void const * _src, t_void * _dst, t_size _size);
t_void * ft_mem_duplicate(t_void const * _mem, t_size _size);
t_void * ft_mem_fill(t_void * _mem, t_byte const _value, t_size _size);
t_void * ft_mem_join(t_void const * _mem_1, t_void const * _mem_2, t_size _size_1, t_size _size_2);
t_void * ft_mem_move(t_void const * _src, t_void * _dst, t_size _size);
t_void * ft_mem_reverse(t_void * _mem, t_size _size);

#endif
