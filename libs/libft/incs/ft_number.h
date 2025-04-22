#ifndef LIBFT_NUMBER_H
#define LIBFT_NUMBER_H

#include "ft_types.h"

// Define ----------------------------------------------------------------------
#define FT_NBR_BASE_BIN "01"
#define FT_NBR_BASE_OCT "01234567"
#define FT_NBR_BASE_DEC "0123456789"
#define FT_NBR_BASE_HEX "0123456789ABCDEF"

// Function --------------------------------------------------------------------
t_char * ft_short_to_str(t_short _nbr, t_char * _buffer);
t_char * ft_int_to_str(t_int _nbr, t_char * _buffer);
t_char * ft_long_to_str(t_long _nbr, t_char * _buffer);
t_char * ft_llong_to_str(t_llong _nbr, t_char * _buffer);

t_char * ft_ushort_to_str(t_ushort _nbr, t_char * _buffer);
t_char * ft_uint_to_str(t_uint _nbr, t_char * _buffer);
t_char * ft_ulong_to_str(t_ulong _nbr, t_char * _buffer);
t_char * ft_ullong_to_str(t_ullong _nbr, t_char * _buffer);

t_char * ft_short_to_str_base(t_short _nbr, t_char * _buffer, t_char const * const _base);
t_char * ft_int_to_str_base(t_int _nbr, t_char * _buffer, t_char const * const _base);
t_char * ft_long_to_str_base(t_long _nbr, t_char * _buffer, t_char const * const _base);
t_char * ft_llong_to_str_base(t_llong _nbr, t_char * _buffer, t_char const * const _base);

t_char * ft_ushort_to_str_base(t_ushort _nbr, t_char * _buffer, t_char const * const _base);
t_char * ft_uint_to_str_base(t_uint _nbr, t_char * _buffer, t_char const * const _base);
t_char * ft_ulong_to_str_base(t_ulong _nbr, t_char * _buffer, t_char const * const _base);
t_char * ft_ullong_to_str_base(t_ullong _nbr, t_char * _buffer, t_char const * const _base);

#endif
