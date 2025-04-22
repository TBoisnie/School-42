#include "libft.h"

// Declare ---------------------------------------------------------------------
#define GENERATE_FN(type, size) \
	t_char const * \
	ft_str_to_##type##_##size( \
		t_char const * _str, \
		t_##type##_##size * _nbr \
	) \
	{ \
		return (ft_str_to_##type##_##size##_base(_str, _nbr, FT_STR_INT_BASE_DEC)); \
	}

#define GENERATE_FN_BASE(type, size) \
	t_char const * \
	ft_str_to_##type##_##size##_base( \
		t_char const * _str, \
		t_##type##_##size * _nbr, \
		t_char const * const _base \
	) \
	{ \
		*_nbr = (t_##type##_##size) _str_to_##type##_base_safe(_str, &_str, _base); \
		return (_str); \
	}

// Declaration -----------------------------------------------------------------
static t_char * _str_to_int_base(t_char const * _str, t_int_64 * _nbr, t_char const * const _base);
static t_char * _str_to_uint_base(t_char const * _str, t_uint_64 * _nbr, t_char const * const _base);
static t_int_64  _str_to_int_base_safe(t_char const * _str, t_char const ** _end, t_char const * const _base);
static t_uint_64 _str_to_uint_base_safe(t_char const * _str, t_char const ** _end, t_char const * const _base);

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
static t_int_64
_str_to_int_base_safe(
	t_char const * _str,
	t_char const ** _end,
	t_char const * const _base
)
{
	t_int_64 value = 0;

	*_end = _str_to_int_base(_str, &value, _base);

	return (value);
}

static t_uint_64
_str_to_uint_base_safe(
	t_char const * _str,
	t_char const ** _end,
	t_char const * const _base
)
{
	t_uint_64 value = 0;

	*_end = _str_to_uint_base(_str, &value, _base);

	return (value);
}

static t_char *
_str_to_int_base(
	t_char const * _str,
	t_int_64 * _nbr,
	t_char const * const _base
)
{
	t_bool is_neg = false;

	switch (*_str)
	{
		case '-':
			is_neg = true;
			_str++;
			break;
		case '+':
			_str++;
			break;
	}

	t_uint_64 value;
	_str = _str_to_uint_base(_str, &value, _base);

	if (!_str)
		return (nullptr);

	*_nbr = (is_neg) ? -value : value;

	return ((t_char *) _str);
}

static t_char *
_str_to_uint_base(
	t_char const * _str,
	t_uint_64 * _nbr,
	t_char const * const _base
)
{
	t_char const * found;

	if (!(found = ft_str_find_chr(_base, *_str)))
		return (nullptr);

	t_size base_size = ft_str_length(_base);

	*_nbr = 0;
	while ((found = ft_str_find_chr(_base, *_str)))
	{
		*_nbr = *_nbr * base_size + (found - _base);

		_str++;
	}

	return ((t_char *) _str);
}
