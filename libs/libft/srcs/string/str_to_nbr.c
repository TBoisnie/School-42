#include "ft_number.h"
#include "ft_string.h"

// Declaration -----------------------------------------------------------------
static t_llong
_str_to_signed_base_safe(t_char const * _str, t_char const ** _end, t_char const * const _base);
static t_ullong
_str_to_unsigned_base_safe(t_char const * _str, t_char const ** _end, t_char const * const _base);
static t_char *
_str_to_signed_base(t_char const * _str, t_llong * _nbr, t_char const * const _base);
static t_char *
_str_to_unsigned_base(t_char const * _str, t_ullong * _nbr, t_char const * const _base);

// Function --------------------------------------------------------------------
t_char const *
ft_str_to_short(
	t_char const * _str,
	t_short * _nbr
)
{
	return (ft_str_to_short_base(_str, _nbr, FT_NBR_BASE_DEC));
}

t_char const *
ft_str_to_int(
	t_char const * _str,
	t_int * _nbr
)
{
	return (ft_str_to_int_base(_str, _nbr, FT_NBR_BASE_DEC));
}

t_char const *
ft_str_to_long(
	t_char const * _str,
	t_long * _nbr
)
{
	return (ft_str_to_long_base(_str, _nbr, FT_NBR_BASE_DEC));
}

t_char const *
ft_str_to_llong(
	t_char const * _str,
	t_llong * _nbr
)
{
	return (ft_str_to_llong_base(_str, _nbr, FT_NBR_BASE_DEC));
}

t_char const *
ft_str_to_ushort(
	t_char const * _str,
	t_ushort * _nbr
)
{
	return (ft_str_to_ushort_base(_str, _nbr, FT_NBR_BASE_DEC));
}

t_char const *
ft_str_to_uint(
	t_char const * _str,
	t_uint * _nbr
)
{
	return (ft_str_to_uint_base(_str, _nbr, FT_NBR_BASE_DEC));
}

t_char const *
ft_str_to_ulong(
	t_char const * _str,
	t_ulong * _nbr
)
{
	return (ft_str_to_ulong_base(_str, _nbr, FT_NBR_BASE_DEC));
}

t_char const *
ft_str_to_ullong(
	t_char const * _str,
	t_ullong * _nbr
)
{
	return (ft_str_to_ullong_base(_str, _nbr, FT_NBR_BASE_DEC));
}

t_char const *
ft_str_to_short_base(
	t_char const * _str,
	t_short * _nbr,
	t_char const * const _base
)
{
	*_nbr = (t_short)_str_to_signed_base_safe(_str, &_str, _base);
	return (_str);
}

t_char const *
ft_str_to_int_base(
	t_char const * _str,
	t_int * _nbr,
	t_char const * const _base
)
{
	*_nbr = (t_int)_str_to_signed_base_safe(_str, &_str, _base);
	return (_str);
}

t_char const *
ft_str_to_long_base(
	t_char const * _str,
	t_long * _nbr,
	t_char const * const _base
)
{
	*_nbr = (t_long)_str_to_signed_base_safe(_str, &_str, _base);
	return (_str);
}

t_char const *
ft_str_to_llong_base(
	t_char const * _str,
	t_llong * _nbr,
	t_char const * const _base
)
{
	*_nbr = (t_llong)_str_to_signed_base_safe(_str, &_str, _base);
	return (_str);
}

t_char const *
ft_str_to_ushort_base(
	t_char const * _str,
	t_ushort * _nbr,
	t_char const * const _base
)
{
	*_nbr = (t_ushort)_str_to_unsigned_base_safe(_str, &_str, _base);
	return (_str);
}

t_char const *
ft_str_to_uint_base(
	t_char const * _str,
	t_uint * _nbr,
	t_char const * const _base
)
{
	*_nbr = (t_uint)_str_to_unsigned_base_safe(_str, &_str, _base);
	return (_str);
}

t_char const *
ft_str_to_ulong_base(
	t_char const * _str,
	t_ulong * _nbr,
	t_char const * const _base
)
{
	*_nbr = (t_ulong)_str_to_unsigned_base_safe(_str, &_str, _base);
	return (_str);
}

t_char const *
ft_str_to_ullong_base(
	t_char const * _str,
	t_ullong * _nbr,
	t_char const * const _base
)
{
	*_nbr = (t_ullong)_str_to_unsigned_base_safe(_str, &_str, _base);
	return (_str);
}

// Static ----------------------------------------------------------------------
static t_llong
_str_to_signed_base_safe(
	t_char const * _str,
	t_char const ** _end,
	t_char const * const _base
)
{
	t_llong value = 0;

	*_end = _str_to_signed_base(_str, &value, _base);

	return (value);
}

static t_ullong
_str_to_unsigned_base_safe(
	t_char const * _str,
	t_char const ** _end,
	t_char const * const _base
)
{
	t_ullong value = 0;

	*_end = _str_to_unsigned_base(_str, &value, _base);

	return (value);
}

static t_char *
_str_to_signed_base(
	t_char const * _str,
	t_llong * _nbr,
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

	t_ullong value;
	_str = _str_to_unsigned_base(_str, &value, _base);

	if (!_str)
		return (nullptr);

	*_nbr = (is_neg) ? -value : value;

	return ((t_char *)_str);
}

static t_char *
_str_to_unsigned_base(
	t_char const * _str,
	t_ullong * _nbr,
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

	return ((t_char *)_str);
}
