#include "ft_number.h"
#include "ft_string.h"

// Declaration -----------------------------------------------------------------
static t_char *
_signed_to_str_base(t_llong _nbr, t_char * _buffer, t_char const * const _base);
static t_char *
_unsigned_to_str_base(t_ullong _nbr, t_char * _buffer, t_char const * const _base);

// Function --------------------------------------------------------------------
t_char *
ft_short_to_str(
	t_short _nbr,
	t_char * _buffer
)
{
	return (_signed_to_str_base(_nbr, _buffer, FT_NBR_BASE_DEC));
}

t_char *
ft_int_to_str(
	t_int _nbr,
	t_char * _buffer
)
{
	return (_signed_to_str_base(_nbr, _buffer, FT_NBR_BASE_DEC));
}

t_char *
ft_long_to_str(
	t_long _nbr,
	t_char * _buffer
)
{
	return (_signed_to_str_base(_nbr, _buffer, FT_NBR_BASE_DEC));
}

t_char *
ft_llong_to_str(
	t_llong _nbr,
	t_char * _buffer
)
{
	return (_signed_to_str_base(_nbr, _buffer, FT_NBR_BASE_DEC));
}

t_char *
ft_ushort_to_str(
	t_ushort _nbr,
	t_char * _buffer
)
{
	return (_unsigned_to_str_base(_nbr, _buffer, FT_NBR_BASE_DEC));
}

t_char *
ft_uint_to_str(
	t_uint _nbr,
	t_char * _buffer
)
{
	return (_unsigned_to_str_base(_nbr, _buffer, FT_NBR_BASE_DEC));
}

t_char *
ft_ulong_to_str(
	t_ulong _nbr,
	t_char * _buffer
)
{
	return (_unsigned_to_str_base(_nbr, _buffer, FT_NBR_BASE_DEC));
}

t_char *
ft_ullong_to_str(
	t_ullong _nbr,
	t_char * _buffer
)
{
	return (_unsigned_to_str_base(_nbr, _buffer, FT_NBR_BASE_DEC));
}

t_char *
ft_short_to_str_base(
	t_short _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	return (_signed_to_str_base(_nbr, _buffer, _base));
}

t_char *
ft_int_to_str_base(
	t_int _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	return (_signed_to_str_base(_nbr, _buffer, _base));
}

t_char *
ft_long_to_str_base(
	t_long _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	return (_signed_to_str_base(_nbr, _buffer, _base));
}

t_char *
ft_llong_to_str_base(
	t_llong _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	return (_signed_to_str_base(_nbr, _buffer, _base));
}

t_char *
ft_ushort_to_str_base(
	t_ushort _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	return (_unsigned_to_str_base(_nbr, _buffer, _base));
}

t_char *
ft_uint_to_str_base(
	t_uint _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	return (_unsigned_to_str_base(_nbr, _buffer, _base));
}

t_char *
ft_ulong_to_str_base(
	t_ulong _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	return (_unsigned_to_str_base(_nbr, _buffer, _base));
}

t_char *
ft_ullong_to_str_base(
	t_ullong _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	return (_unsigned_to_str_base(_nbr, _buffer, _base));
}

// Static ----------------------------------------------------------------------
static t_char *
_signed_to_str_base(
	t_llong _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	t_ullong value = _nbr;

	if (_nbr < 0)
	{
		*_buffer++ = '-';
		value = -_nbr;
	}

	return (_unsigned_to_str_base(value, _buffer, _base));
}

static t_char *
_unsigned_to_str_base(
	t_ullong _nbr,
	t_char * _buffer,
	t_char const * const _base
)
{
	t_size base_size = ft_str_length(_base);

	t_char * cursor = _buffer;
	do
	{
		*cursor++ = _base[_nbr % base_size];
	}
	while ((_nbr /= base_size));

	*cursor = '\0';
	ft_str_reverse(_buffer);

	return (cursor);
}
