#include "libft.h"

// Macro -----------------------------------------------------------------------
#define GENERATE_FN(type, size) \
	t_uint_##size \
	ft_sys_to_##type##_endian_##size( \
		t_uint_##size _mem \
	) \
	{ \
		if ( ft_sys_is_##type##_endian() ) \
		{ \
			return ( _mem ); \
		} \
		\
		return ( FT_MEM_BYTE_ENDIAN_SWAP_##size(_mem) ); \
	}

// Typedef ---------------------------------------------------------------------
typedef union u_endian t_endian;

// Union -----------------------------------------------------------------------
union u_endian
{
	t_uint i;
	t_byte b;
};

// Function --------------------------------------------------------------------
t_bool
ft_sys_is_big_endian()
{
	t_endian endian =
	{
		.i = 1
	};

	return (endian.b == 0);
}

t_bool
ft_sys_is_little_endian()
{
	t_endian endian =
	{
		.i = 1
	};

	return (endian.b == 1);
}

GENERATE_FN(little, 16);
GENERATE_FN(little, 32);
GENERATE_FN(little, 64);

GENERATE_FN(big, 16);
GENERATE_FN(big, 32);
GENERATE_FN(big, 64);
