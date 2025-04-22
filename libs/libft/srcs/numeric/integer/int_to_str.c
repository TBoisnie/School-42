#include "libft.h"

// Macro -----------------------------------------------------------------------
#define GENERATE_FN(type, size) \
	t_char * \
	ft_##type##_##size##_to_str( \
		t_##type##_##size _##type, \
		t_char * _buffer \
	) \
	{ \
		return (_##type##_to_str_base(_##type, _buffer, FT_STR_INT_BASE_DEC)); \
	}

#define GENERATE_FN_BASE(type, size) \
	t_char * \
	ft_##type##_##size##_to_str_base( \
		t_##type##_##size _##type, \
		t_char * _buffer, \
		t_char const * const _base \
	) \
	{ \
		return (_##type##_to_str_base(_##type, _buffer, _base)); \
	}

// Declaration -----------------------------------------------------------------
static t_char * _int_to_str_base(t_int_64 _int, t_char * _buffer, t_char const * const _base);
static t_char * _uint_to_str_base(t_uint_64 _uint, t_char * _buffer, t_char const * const _base);

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

// Static ----------------------------------------------------------------------
static t_char *
_int_to_str_base(
	t_int_64 _int,
	t_char * _buffer,
	t_char const * const _base
)
{
	t_uint_64 value = _int;

	if (_int < 0)
	{
		*_buffer++ = '-';
		value = -_int;
	}

	return (_uint_to_str_base(value, _buffer, _base));
}

static t_char *
_uint_to_str_base(
	t_uint_64 _uint,
	t_char * _buffer,
	t_char const * const _base
)
{
	t_size base_size = ft_str_length(_base);

	t_char * cursor = _buffer;
	do
	{
		*cursor++ = _base[_uint % base_size];
	}
	while ((_uint /= base_size));

	*cursor = '\0';
	ft_str_reverse(_buffer);

	return (cursor);
}
