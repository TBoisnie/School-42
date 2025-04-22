#ifndef LIBFT_NUMERIC_INTEGER_H
#define LIBFT_NUMERIC_INTEGER_H

#include "../core/ft_types.h"

// Function --------------------------------------------------------------------
/**
 * Convert an integer into its string representation (using base).
 *
 * @param _int: Integer to convert
 * @param _buffer: String to store the representation
 * @param _base: Base to convert
 *
 * @return Converted string
**/
t_char * ft_int_8_to_str(t_int_8 _int, t_char * _buffer);
t_char * ft_int_16_to_str(t_int_16 _int, t_char * _buffer);
t_char * ft_int_32_to_str(t_int_32 _int, t_char * _buffer);
t_char * ft_int_64_to_str(t_int_64 _int, t_char * _buffer);

t_char * ft_uint_8_to_str(t_uint_8 _uint, t_char * _buffer);
t_char * ft_uint_16_to_str(t_uint_16 _uint, t_char * _buffer);
t_char * ft_uint_32_to_str(t_uint_32 _uint, t_char * _buffer);
t_char * ft_uint_64_to_str(t_uint_64 _uint, t_char * _buffer);

t_char * ft_int_8_to_str_base(t_int_8 _int, t_char * _buffer, t_char const * const _base);
t_char * ft_int_16_to_str_base(t_int_16 _int, t_char * _buffer, t_char const * const _base);
t_char * ft_int_32_to_str_base(t_int_32 _int, t_char * _buffer, t_char const * const _base);
t_char * ft_int_64_to_str_base(t_int_64 _int, t_char * _buffer, t_char const * const _base);

t_char * ft_uint_8_to_str_base(t_uint_8 _uint, t_char * _buffer, t_char const * const _base);
t_char * ft_uint_16_to_str_base(t_uint_16 _uint, t_char * _buffer, t_char const * const _base);
t_char * ft_uint_32_to_str_base(t_uint_32 _uint, t_char * _buffer, t_char const * const _base);
t_char * ft_uint_64_to_str_base(t_uint_64 _uint, t_char * _buffer, t_char const * const _base);

#endif
