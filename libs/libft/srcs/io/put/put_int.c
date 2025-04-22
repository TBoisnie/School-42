#include <unistd.h>
#include "libft.h"

// Macro -----------------------------------------------------------------------
#define GENERATE_FN(type, size) \
	t_void \
	ft_io_put_##type##_##size( \
		t_fd _fd, \
		t_##type##_##size _##type \
	) \
	{ \
		ft_io_put_##type##_##size##_base(_fd, _##type, FT_STR_INT_BASE_DEC); \
	}

#define GENERATE_FN_BASE(type, size) \
	t_void \
	ft_io_put_##type##_##size##_base( \
		t_fd _fd, \
		t_##type##_##size _##type, \
		t_char const * const _base \
	) \
	{ \
		t_char buffer[size + 2]; \
		\
		ft_##type##_##size##_to_str_base(_##type, buffer, _base); \
		\
		ft_io_put_str(_fd, buffer); \
	}

// Function --------------------------------------------------------------------
GENERATE_FN(int, 8)
GENERATE_FN(int, 16)
GENERATE_FN(int, 32)
GENERATE_FN(int, 64)

GENERATE_FN(uint, 8)
GENERATE_FN(uint, 16)
GENERATE_FN(uint, 32)
GENERATE_FN(uint, 64)

GENERATE_FN_BASE(int, 8)
GENERATE_FN_BASE(int, 16)
GENERATE_FN_BASE(int, 32)
GENERATE_FN_BASE(int, 64)

GENERATE_FN_BASE(uint, 8)
GENERATE_FN_BASE(uint, 16)
GENERATE_FN_BASE(uint, 32)
GENERATE_FN_BASE(uint, 64)
