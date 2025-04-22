#ifndef LIBFT_ALPHABETIC_STRING_H
#define LIBFT_ALPHABETIC_STRING_H

#include "../core/ft_types.h"

// Define ----------------------------------------------------------------------
#define FT_STR_INT_BASE_HEX "0123456789ABCDEF"
#define FT_STR_INT_BASE_DEC "0123456789"
#define FT_STR_INT_BASE_OCT "01234567"
#define FT_STR_INT_BASE_BIN "01"

// Function --------------------------------------------------------------------
/**
 * Get the length of a string.
 *
 * @param _str: String to get the length of
 *
 * @return Length of the string
**/
t_size ft_str_length(t_char const * _str);

/**
 * Reverse a string in-place.
 *
 * @param _str: String to reverse
 *
 * @return Reversed string
**/
t_char * ft_str_reverse(t_char * _str);

/**
 * Remove any characters in _trim from the beginning and end of _str in-place.
 *
 * @param _str: String to trim
 * @param _trim: String containing characters to trim
 *
 * @return Trimmed string
**/
t_char * ft_str_trim(t_char * _str, t_char const * const _trim);

/**
 * Append a string to anothe one.
 *
 * @param _dst: String to append to
 * @param _src: String to append
 *
 * @return Concatenated string
**/
t_char * ft_str_concat(t_char * _dst, t_char const * _src);

/**
 * Append a string to anothe one, up to a length limit.
 *
 * @param _dst: String to append to
 * @param _src: String to append
 * @param _limit: Concatenated string length limit
 *
 * @return Concatenated string
**/
t_char * ft_str_concat_limit(t_char * _dst, t_char const * _src, t_size _limit);

/**
 * Copy a string into another one.
 *
 * @param _src: String to copy from
 * @param _dst: String to copy to
 *
 * @return Copied string
**/
t_char * ft_str_copy(t_char const * _src, t_char * _dst);

/**
 * Copy a string into another one, up to a length limit.
 *
 * @param _src: String to copy from
 * @param _dst: String to copy to
 * @param _limit: String length limit
 *
 * @return Copied string
**/
t_char * ft_str_copy_limit(t_char const * _src, t_char * _dst, t_size _limit);

/**
 * Copy a string into new allocated one.
 *
 * @param _str: String to copy
 *
 * @return Newly allocated copied string
**/
t_char * ft_str_duplicate(t_char const * _str);

/**
 * Copy a string into new allocated one, up to a length limit.
 *
 * @param _str: String to copy
 * @param _limit: String length limit
 *
 * @return Newly allocated copied string
**/
t_char * ft_str_duplicate_limit(t_char const * _str, t_size _limit);

/**
 * Concatenate 2 strings into a new allocated one.
 *
 * @param _str_1: First string
 * @param _str_2: Second string
 *
 * @return Newly concatenated string
 *
 * @exception If allocation failed, `nullptr` is returned
**/
t_char * ft_str_join(t_char const * _str_1, t_char const * _str_2);

/**
 * Compare 2 strings (case-sensitive).
 *
 * @param _str_1: First string
 * @param _str_2: Second string
 *
 * @return `0` if the strings are identical, `-1` if the first character to mismatch
 * is inferior in _str_1 than in _str_2, `1` otherwise
**/
t_int_8 ft_str_compare(t_char const * _str_1, t_char const * _str_2);

/**
 * Compare 2 strings (case-sensitive), up to a length limit.
 *
 * @param _str_1: First string
 * @param _str_2: Second string
 * @param _limit: Length limit
 *
 * @return `0` if the strings are identical, `-1` if the first character to mismatch
 * is inferior in _str_1 than in _str_2, `1` otherwise
**/
t_int_8 ft_str_compare_limit(t_char const * _str_1, t_char const * _str_2, t_size _limit);

/**
 * Compare 2 strings (case-insensitive).
 *
 * @param _str_1: First string
 * @param _str_2: Second string
 *
 * @return `0` if the strings are identical, `-1` if the first character to mismatch
 * is inferior in _str_1 than in _str_2, `1` otherwise
**/
t_int_8 ft_str_icompare(t_char const * _str_1, t_char const * _str_2);

/**
 * Compare 2 strings (case-insensitive), up to a length limit.
 *
 * @param _str_1: First string
 * @param _str_2: Second string
 * @param _limit: Length limit
 *
 * @return `0` if the strings are identical, `-1` if the first character to mismatch
 * is inferior in _str_1 than in _str_2, `1` otherwise
**/
t_int_8 ft_str_icompare_limit(t_char const * _str_1, t_char const * _str_2, t_size _limit);

/**
 * Search for the first occurrence of a character into a string.
 *
 * @param _haystack: String to search from
 * @param _needle: Character to search for
 *
 * @return Pointer to the found occurrence
 *
 * @exception If the `_needle` is not present, `nullptr` is returned
**/
t_char * ft_str_find_chr(t_char const * _haystack, t_char const _needle);

/**
 * Search for the first occurrence of a substring into a string.
 *
 * @param _haystack: String to search from
 * @param _needle: Substring to search for
 *
 * @return Pointer to the found occurrence
 *
 * @exception If the `_needle` is not present, `nullptr` is returned
**/
t_char * ft_str_find_str(t_char const * _haystack, t_char const * _needle);

/**
 * Search for the last occurrence of a character into a string.
 *
 * @param _haystack: String to search from
 * @param _needle: Character to search for
 *
 * @return Pointer to the found occurrence
 *
 * @exception If the `_needle` is not present, `nullptr` is returned
**/
t_char * ft_str_rfind_chr(t_char const * _haystack, t_char const _needle);

/**
 * Search for the last occurrence of a substring into a string.
 *
 * @param _haystack: String to search from
 * @param _needle: Substring to search for
 *
 * @return Pointer to the found occurrence
 *
 * @exception If the `_needle` is not present, `nullptr` is returned
**/
t_char * ft_str_rfind_str(t_char const * _haystack, t_char const * _needle);

/**
 * Convert string to lower-case in-place.
 *
 * @param _str: String to convert
 *
 * @return Converted string
**/
t_char * ft_str_to_lower(t_char * _str);

/**
 * Convert string to upper-case in-place.
 *
 * @param _str: String to convert
 *
 * @return Converted string
**/
t_char * ft_str_to_upper(t_char * _str);

/**
 * Convert a string into an integer.
 *
 * @param _str: String to convert
 * @param _int: Pointer to the converted integer
 *
 * @return Pointer to the end of the integer representation in `_str`
**/
t_char const * ft_str_to_int_8(t_char const * _str, t_int_8 * _int);
t_char const * ft_str_to_int_16(t_char const * _str, t_int_16 * _int);
t_char const * ft_str_to_int_32(t_char const * _str, t_int_32 * _int);
t_char const * ft_str_to_int_64(t_char const * _str, t_int_64 * _int);

t_char const * ft_str_to_uint_8(t_char const * _str,  t_uint_8 * _uint);
t_char const * ft_str_to_uint_16(t_char const * _str, t_uint_16 * _uint);
t_char const * ft_str_to_uint_32(t_char const * _str, t_uint_32 * _uint);
t_char const * ft_str_to_uint_64(t_char const * _str, t_uint_64 * _uint);

t_char const * ft_str_to_int_8_base(t_char const * _str, t_int_8 * _int, t_char const * const _base);
t_char const * ft_str_to_int_16_base(t_char const * _str, t_int_16 * _int, t_char const * const _base);
t_char const * ft_str_to_int_32_base(t_char const * _str, t_int_32 * _int, t_char const * const _base);
t_char const * ft_str_to_int_64_base(t_char const * _str, t_int_64 * _int, t_char const * const _base);

t_char const * ft_str_to_uint_8_base(t_char const * _str, t_uint_8 * _uint, t_char const * const _base);
t_char const * ft_str_to_uint_16_base(t_char const * _str, t_uint_16 * _uint, t_char const * const _base);
t_char const * ft_str_to_uint_32_base(t_char const * _str, t_uint_32 * _uint, t_char const * const _base);
t_char const * ft_str_to_uint_64_base(t_char const * _str, t_uint_64 * _uint, t_char const * const _base);


// t_char ** str_split(t_char const * _str, t_char const * _separator);
// t_char *  str_replace(t_char const * _str, t_char const * _find, t_char const * _replacement);
// t_char *  str_map(t_char * _str, t_char (* _apply)(t_char _c, t_size _index));

#endif
