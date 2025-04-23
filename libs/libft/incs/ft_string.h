#ifndef LIBFT_STRING_H
#define LIBFT_STRING_H

#include "ft_types.h"

// Function --------------------------------------------------------------------
t_char * ft_str_join(t_char const * _str_1, t_char const * _str_2);
t_size   ft_str_length(t_char const * _str);
t_char * ft_str_reverse(t_char * _str);
t_char * ft_str_trim(t_char * _str, t_char const * const _trim);

t_char * ft_str_to_lower(t_char * _str);
t_char * ft_str_to_upper(t_char * _str);

t_char * ft_str_concat(t_char * _dst, t_char const * _src);
t_char * ft_str_concat_limit(t_char * _dst, t_char const * _src, t_size _limit);
t_int    ft_str_compare(t_char const * _str_1, t_char const * _str_2);
t_int    ft_str_compare_limit(t_char const * _str_1, t_char const * _str_2, t_size _limit);
t_int    ft_str_icompare(t_char const * _str_1, t_char const * _str_2);
t_int    ft_str_icompare_limit(t_char const * _str_1, t_char const * _str_2, t_size _limit);
t_char * ft_str_copy(t_char const * _src, t_char * _dst);
t_char * ft_str_copy_limit(t_char const * _src, t_char * _dst, t_size _limit);
t_char * ft_str_duplicate(t_char const * _str);
t_char * ft_str_duplicate_limit(t_char const * _str, t_size _limit);

t_char * ft_str_find_chr(t_char const * _haystack, t_char const _needle);
t_char * ft_str_find_str(t_char const * _haystack, t_char const * _needle);
t_char * ft_str_rfind_chr(t_char const * _haystack, t_char const _needle);
t_char * ft_str_rfind_str(t_char const * _haystack, t_char const * _needle);

// t_char ** str_split(t_char const * _str, t_char const * _separator);
// t_char *  str_replace(t_char const * _str, t_char const * _find, t_char const * _replacement);
// t_char *  str_map(t_char * _str, t_char (* _apply)(t_char _c, t_size _index));

t_char const * ft_str_to_short(t_char const * _str, t_short * _nbr);
t_char const * ft_str_to_int(t_char const * _str, t_int * _nbr);
t_char const * ft_str_to_long(t_char const * _str, t_long * _nbr);
t_char const * ft_str_to_llong(t_char const * _str, t_llong * _nbr);

t_char const * ft_str_to_ushort(t_char const * _str, t_ushort * _nbr);
t_char const * ft_str_to_uint(t_char const * _str, t_uint * _nbr);
t_char const * ft_str_to_ulong(t_char const * _str, t_ulong * _nbr);
t_char const * ft_str_to_ullong(t_char const * _str, t_ullong * _nbr);

t_char const * ft_str_to_short_base(t_char const * _str, t_short * _nbr, t_char const * const _base);
t_char const * ft_str_to_int_base(t_char const * _str, t_int * _nbr, t_char const * const _base);
t_char const * ft_str_to_long_base(t_char const * _str, t_long * _nbr, t_char const * const _base);
t_char const * ft_str_to_llong_base(t_char const * _str, t_llong * _nbr, t_char const * const _base);

t_char const * ft_str_to_ushort_base(t_char const * _str, t_ushort * _nbr, t_char const * const _base);
t_char const * ft_str_to_uint_base(t_char const * _str, t_uint * _nbr, t_char const * const _base);
t_char const * ft_str_to_ulong_base(t_char const * _str, t_ulong * _nbr, t_char const * const _base);
t_char const * ft_str_to_ullong_base(t_char const * _str, t_ullong * _nbr, t_char const * const _base);

#endif
