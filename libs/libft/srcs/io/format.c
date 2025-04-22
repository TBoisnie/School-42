#include "ft_console.h"
#include "ft_io.h"
#include "ft_char.h"
#include "ft_math.h"
#include "ft_memory.h"
#include "ft_math.h"
#include "ft_number.h"
#include "ft_string.h"

// Define ----------------------------------------------------------------------
// %[$][flags][width][.precision][length modifier]conversion
#define FLAG_PLUS     (1u << 0)
#define FLAG_MINUS    (1u << 1)
#define FLAG_HASH     (1u << 2)
#define FLAG_ZERO     (1u << 3)
#define FLAG_SPACE    (1u << 4)

#define LENGTH_CHAR   (1u << 0)
#define LENGTH_SHORT  (1u << 1)
#define LENGTH_LONG   (1u << 3)
#define LENGTH_LLONG  (1u << 4)

#define HAS_WIDTH     (1u << 0)
#define HAS_PRECISION (1u << 1)

// Struct ----------------------------------------------------------------------
typedef struct s_state       t_state;
typedef struct s_placeholder t_placeholder;

typedef t_void (* t_func_out)(t_char _chr, t_state * _state, t_bool _force_null);

struct s_placeholder
{
	t_byte flags;
	t_ulong width;
	t_ulong precision;
	t_byte length;
	t_char type;
	t_byte marker;
};

struct s_state
{
	t_size index;
	t_size max_length;

	t_char * buffer;
	t_size offset;
	t_fd fd;

	t_func_out out;
};

// Declaration -----------------------------------------------------------------
static t_void _format(t_char const * _fmt, va_list * _args, t_state * state);

static t_char const * _check_flags(t_char const * _fmt, va_list * _args, t_placeholder * _ph);
static t_char const * _check_length(t_char const * _fmt, va_list * _args, t_placeholder * _ph);
static t_char const * _check_precision(t_char const * _fmt, va_list * _args, t_placeholder * _ph);
static t_char const * _check_type(t_char const * _fmt, va_list * _args, t_placeholder * _ph);
static t_char const * _check_width(t_char const * _fmt, va_list * _args, t_placeholder * _ph);

static t_void _convert_chr(va_list *_args, t_placeholder * _ph, t_state * _state);
static t_void _convert_nbr(va_list *_args, t_placeholder * _ph, t_state * _state);
static t_void _convert_str(va_list *_args, t_placeholder * _ph, t_state * _state);

// static t_void _out_buffer(t_char _chr, t_state * _state);
static t_void _out_fd(t_char _chr, t_state * _state, t_bool _force_null);

// Function --------------------------------------------------------------------
t_size
ft_printf(
	t_char const * _fmt,
	...
)
{
	t_char buffer[FT_PRINTF_BUFFER_SIZE];
	ft_mem_fill(buffer, '\0', FT_PRINTF_BUFFER_SIZE);

	t_state state =
	{
		.index = 0,
		.max_length = -1,
		.buffer = buffer,
		.offset = 0,
		.fd = FT_CONSOLE_FD_OUT,
		.out = _out_fd
	};

	va_list args;
	va_start(args, _fmt);
	_format(_fmt, &args, &state);
	va_end(args);

	return (state.index);
}

t_size
ft_fprintf(
	t_fd _fd,
	t_char const * _fmt,
	...
)
{
	t_char buffer[FT_PRINTF_BUFFER_SIZE];
	ft_mem_fill(buffer, '\0', FT_PRINTF_BUFFER_SIZE);

	t_state state =
	{
		.index = 0,
		.max_length = -1,
		.buffer = buffer,
		.offset = 0,
		.fd = _fd,
		.out = _out_fd
	};

	va_list args;
	va_start(args, _fmt);
	_format(_fmt, &args, &state);
	va_end(args);

	return (state.index);
}


// Static ----------------------------------------------------------------------
static t_void
_format(
	t_char const * _fmt,
	va_list * _args,
	t_state * _state
)
{
	t_placeholder ph;

	while (*_fmt)
	{
		if (*_fmt != '%')
		{
			_state->out(*_fmt++, _state, false);
			continue;
		}

		_fmt++;

		FT_MEM_BIT_CLEAR(ph.flags);
		FT_MEM_BIT_CLEAR(ph.marker);
		FT_MEM_BIT_CLEAR(ph.length);
		ph.precision = 0;
		ph.width = 0;
		ph.type = '\0';

		_fmt = _check_flags(_fmt, _args, &ph);
		_fmt = _check_width(_fmt, _args, &ph);
		_fmt = _check_precision(_fmt, _args, &ph);
		_fmt = _check_length(_fmt, _args, &ph);
		_fmt = _check_type(_fmt, _args, &ph);

		switch (ph.type)
		{
			case 'd':
			case 'i':
			case 'u':
			case 'x':
			case 'X':
			case 'o':
			case 'b':
			case 'p':
				_convert_nbr(_args, &ph, _state);
				break;

			case 'c':
				_convert_chr(_args, &ph, _state);
				break;

			case 's':
				_convert_str(_args, &ph, _state);
				break;

			case '%':
				_state->out(ph.type, _state, false);
				break;

			default:
				_state->out(ph.type, _state, false);
				// _convert_unknown(_args, &ph, _state);
				break;
		}
	}

	_state->out('\0', _state, false);
}

static t_char const *
_check_flags(
	t_char const * _fmt,
	va_list * _args,
	t_placeholder * _ph
)
{
	(void) _args;

	t_bool match = true;
	do
	{
		switch (*_fmt++)
		{
			case '+':
				FT_MEM_BIT_SET(_ph->flags, FLAG_PLUS);
				FT_MEM_BIT_UNSET(_ph->flags, FLAG_SPACE);
				break;

			case '-':
				FT_MEM_BIT_SET(_ph->flags, FLAG_MINUS);
				FT_MEM_BIT_UNSET(_ph->flags, FLAG_ZERO);
				break;

			case '#':
				FT_MEM_BIT_SET(_ph->flags, FLAG_HASH);
				break;

			case '0':
				if (!FT_MEM_BIT_ISSET(_ph->flags, FLAG_MINUS))
					FT_MEM_BIT_SET(_ph->flags, FLAG_ZERO);
				break;

			case ' ':
				if (!FT_MEM_BIT_ISSET(_ph->flags, FLAG_PLUS))
					FT_MEM_BIT_SET(_ph->flags, FLAG_SPACE);
				break;

			default:
				match = false;
				break;
		}
	} while (match);

	return (--_fmt);
}

static t_char const *
_check_length(
	t_char const * _fmt,
	va_list * _args,
	t_placeholder * _ph
)
{
	(void) _args;

	switch (*_fmt)
	{
		case 'h':
			_fmt++;

			if (*_fmt == 'h')
			{
				_fmt++;
				FT_MEM_BIT_SET(_ph->length, LENGTH_CHAR);
				break;
			}

			FT_MEM_BIT_SET(_ph->length, LENGTH_SHORT);
			break;

		case 'l':
			_fmt++;

			if (*_fmt == 'l')
			{
				_fmt++;
				FT_MEM_BIT_SET(_ph->length, LENGTH_LLONG);
				break;
			}

			FT_MEM_BIT_SET(_ph->length, LENGTH_LONG);
			break;

		default:
			break;
	}

	return (_fmt);
}

static t_char const *
_check_precision(
	t_char const * _fmt,
	va_list * _args,
	t_placeholder * _ph
)
{
	if (*_fmt != '.')
		return (_fmt);

	FT_MEM_BIT_SET(_ph->marker, HAS_PRECISION);

	_fmt++;

	if (ft_chr_is_digit(*_fmt))
		return (ft_str_to_ulong(_fmt, &_ph->precision));

	if (*_fmt != '*')
		return (_fmt);

	t_int const p = (t_int)va_arg(*_args, t_int);

	if (p >= 0)
		_ph->precision = (t_ulong)p;
	else
		FT_MEM_BIT_UNSET(_ph->marker, HAS_PRECISION);

	return (++_fmt);
}

static t_char const *
_check_type(
	t_char const * _fmt,
	va_list * _args,
	t_placeholder * _ph
)
{
	(void) _args;

	_ph->type = *_fmt;

	return (++_fmt);
}

static t_char const *
_check_width(
	t_char const * _fmt,
	va_list * _args,
	t_placeholder * _ph
)
{
	if (ft_chr_is_digit(*_fmt))
	{
		FT_MEM_BIT_SET(_ph->marker, HAS_WIDTH);
		return (ft_str_to_ulong(_fmt, &_ph->width));
	}

	if (*_fmt != '*')
		return (_fmt);

	t_long const w = (t_long)va_arg(*_args, t_long);

	if (w >= 0)
		_ph->width = (t_size)w;
	else
	{
		_check_flags("-", _args, _ph);
		_ph->width = (t_size)-w;
	}

	FT_MEM_BIT_SET(_ph->marker, HAS_WIDTH);

	return (++_fmt);
}

static t_void
_convert_chr(
	va_list *_args,
	t_placeholder * _ph,
	t_state * _state
)
{
	t_size wrote = 1;

	if (!FT_MEM_BIT_ISSET(_ph->flags, FLAG_MINUS))
	{
		while (wrote++ < _ph->width)
			_state->out(' ', _state, false);
	}

	_state->out((t_char)va_arg(*_args, t_int), _state, true);

	if (FT_MEM_BIT_ISSET(_ph->flags, FLAG_MINUS))
	{
		while (wrote++ < _ph->width)
			_state->out(' ', _state, false);
	}
}

static t_void
_convert_nbr(
	va_list *_args,
	t_placeholder * _ph,
	t_state * _state
)
{
	if (_ph->type == 'p')
		FT_MEM_BIT_SET(_ph->flags, FLAG_HASH);

	if (FT_MEM_BIT_ISSET(_ph->marker, HAS_PRECISION))
		FT_MEM_BIT_UNSET(_ph->flags, FLAG_ZERO);

	t_ullong value;
	t_bool is_negative = false;
	switch (_ph->type)
	{
		case 'i':
		case 'd':
			switch (_ph->length)
			{
				case LENGTH_LLONG:
				{
					t_llong const v = (t_llong)va_arg(*_args, t_llong);
					value = (v < 0) ? -v : v;
					is_negative = (v < 0);
					break;
				}
				case LENGTH_LONG:
				{
					t_long const v = (t_long)va_arg(*_args, t_long);
					value = (v < 0) ? -v : v;
					is_negative = (v < 0);
					break;
				}
				case LENGTH_SHORT:
				{
					t_short const v = (t_short)va_arg(*_args, t_int);
					value = (v < 0) ? -v : v;
					is_negative = (v < 0);
					break;
				}
				case LENGTH_CHAR:
				{
					t_char const v = (t_char)va_arg(*_args, t_int);
					value = (v < 0) ? -v : v;
					is_negative = (v < 0);
					break;
				}
				default:
				{
					t_int const v = (t_int)va_arg(*_args, t_int);
					value = (v < 0) ? -v : v;
					is_negative = (v < 0);
					break;
				}
			}
			break;
		case 'u':
		case 'x':
		case 'X':
		case 'o':
		case 'b':
			switch (_ph->length)
			{
				case LENGTH_LLONG:
					value = (t_ullong)va_arg(*_args, t_ullong);
					break;
				case LENGTH_LONG:
					value = (t_ulong)va_arg(*_args, t_ulong);
					break;
				case LENGTH_SHORT:
					value = (t_ushort)va_arg(*_args, t_uint);
					break;
				case LENGTH_CHAR:
					value = (t_byte)va_arg(*_args, t_uint);
					break;
				default:
					value = (t_uint)va_arg(*_args, t_uint);
					break;
			}
			break;
		default:
			value = (t_ptr)va_arg(*_args, t_void *);
			break;
	}

	t_char * prefix = nullptr;
	if (_ph->type == 'd' || _ph->type == 'i')
	{
		if (is_negative)
			prefix = "-";
		else
		{
			if (FT_MEM_BIT_ISSET(_ph->flags, FLAG_SPACE))
				prefix = " ";
			if (FT_MEM_BIT_ISSET(_ph->flags, FLAG_PLUS))
				prefix = "+";
		}
	}

	if (FT_MEM_BIT_ISSET(_ph->flags, FLAG_HASH))
	{
		switch (_ph->type)
		{
			case 'x':
			case 'p': prefix = "0x"; break;
			case 'X': prefix = "0X"; break;
			case 'o': prefix = "0o"; break;
			case 'b': prefix = "0b"; break;
		}
	}

	t_char * base;
	switch (_ph->type)
	{
		case 'd':
		case 'i':
		case 'u': base = FT_NBR_BASE_DEC; break;
		case 'x':
		case 'X':
		case 'p': base = FT_NBR_BASE_HEX; break;
		case 'o': base = FT_NBR_BASE_OCT; break;
		case 'b': base = FT_NBR_BASE_BIN; break;
	}

	t_char value_str[64 + 1];
	ft_ullong_to_str_base(value, value_str, base);

	if (_ph->type =='x' || _ph->type == 'p')
		ft_str_to_lower(value_str);

	t_size prefix_length = ft_str_length(prefix);
	t_size value_str_length = ft_str_length(value_str);
	t_size zero_padding_length = 0;

	if (FT_MEM_BIT_ISSET(_ph->flags, FLAG_ZERO))
	{
		if (_ph->width > prefix_length + value_str_length)
			zero_padding_length = _ph->width - value_str_length - prefix_length;
	}
	else if (FT_MEM_BIT_ISSET(_ph->marker, HAS_PRECISION))
	{
		if (_ph->precision > value_str_length)
			zero_padding_length = _ph->precision - value_str_length;
	}

	t_size wrote = prefix_length + zero_padding_length + value_str_length;
	_ph->width = FT_MATH_MAX(wrote, _ph->width);

	if (!FT_MEM_BIT_ISSET(_ph->flags, FLAG_MINUS) &&
		!FT_MEM_BIT_ISSET(_ph->flags, FLAG_ZERO))
	{
		while (wrote++ < _ph->width)
			_state->out(' ', _state, false);
	}

	t_char * cursor;
	if (prefix)
	{
		cursor = prefix;
		while (*cursor)
			_state->out(*cursor++, _state, false);
	}

	while (zero_padding_length--)
		_state->out('0', _state, false);

	cursor = value_str;
	while (*cursor)
		_state->out(*cursor++, _state, false);

	if (FT_MEM_BIT_ISSET(_ph->flags, FLAG_MINUS))
	{
		while (wrote++ < _ph->width)
			_state->out(' ', _state, false);
	}
}

static t_void
_convert_str(
	va_list *_args,
	t_placeholder * _ph,
	t_state * _state
)
{
	t_char const * str = (t_char *)va_arg(*_args, t_char *);
	t_size wrote = ft_str_length(str);

	if (FT_MEM_BIT_ISSET(_ph->marker, HAS_PRECISION))
		wrote = FT_MATH_MIN(wrote, _ph->precision);

	if (!FT_MEM_BIT_ISSET(_ph->flags, FLAG_MINUS))
	{
		while (wrote++ < _ph->width)
			_state->out(' ', _state, false);
	}

	while (*str && (!FT_MEM_BIT_ISSET(_ph->marker, HAS_PRECISION) || _ph->precision--))
		_state->out(*str++, _state, false);

	if (FT_MEM_BIT_ISSET(_ph->flags, FLAG_MINUS))
	{
		while (wrote++ < _ph->width)
			_state->out(' ', _state, false);
	}
}

static t_void
_out_fd(
	t_char _chr,
	t_state * _state,
	t_bool _force_null
)
{
	t_size position = _state->index % FT_PRINTF_BUFFER_SIZE;

	if (position >= FT_PRINTF_BUFFER_SIZE - 1)
	{
		ft_fd_put_str(_state->fd, &_state->buffer[_state->offset]);
		_state->offset = 0;
		ft_mem_fill(_state->buffer, '\0', FT_PRINTF_BUFFER_SIZE);
	}

	if (_state->index < _state->max_length)
	{
		_state->buffer[position] = _chr;
		_state->index++;
	}

	if (_chr == '\0' || _chr == '\n')
	{
		ft_fd_put_str(_state->fd, &_state->buffer[_state->offset]);
		_state->offset = position + 1;
	}

	if (_chr == '\0' && _force_null)
	{
		ft_fd_put_chr(_state->fd, _chr);
	}
}

// static t_void
// _out_buffer(
// 	t_char _chr,
// 	t_state * _state
// )
// {
// 	if (_state->index < _state->max_length)
// 		_state->buffer[_state->index++] = _chr;
// }
