#ifndef LIBFT_LIMITS_H
#define LIBFT_LIMITS_H

// Define ----------------------------------------------------------------------
#define FT_PATH_MAX    (4096)


#define FT_INT_8_MIN   (-127 - 1)
#define FT_INT_16_MIN  (-32767 - 1)
#define FT_INT_32_MIN  (-2147483647 - 1)
#define FT_INT_64_MIN  (-9223372036854775807LL - 1)

#define FT_INT_8_MAX   (127)
#define FT_INT_16_MAX  (32767)
#define FT_INT_32_MAX  (2147483647L)
#define FT_INT_64_MAX  (9223372036854775807LL)

#define FT_UINT_8_MIN  (0U)
#define FT_UINT_16_MIN (0U)
#define FT_UINT_32_MIN (0U)
#define FT_UINT_64_MIN (0U)

#define FT_UINT_8_MAX  (256U)
#define FT_UINT_16_MAX (65535U)
#define FT_UINT_32_MAX (4294967295UL)
#define FT_UINT_64_MAX (18446744073709551615ULL)


#define FT_CHAR_MIN    (FT_INT_8_MIN)
#define FT_SHORT_MIN   (FT_INT_16_MIN)
#define FT_INT_MIN     (FT_INT_32_MIN)
#define FT_LONG_MIN    (FT_INT_32_MIN)
#define FT_LLONG_MIN   (FT_INT_64_MIN)

#define FT_CHAR_MAX    (FT_INT_8_MAX)
#define FT_SHORT_MAX   (FT_INT_16_MAX)
#define FT_INT_MAX     (FT_INT_32_MAX)
#define FT_LONG_MAX    (FT_INT_32_MAX)
#define FT_LLONG_MAX   (FT_INT_64_MAX)

#define FT_UCHAR_MIN   (FT_UINT_8_MIN)
#define FT_USHORT_MIN  (FT_UINT_16_MIN)
#define FT_UINT_MIN    (FT_UINT_32_MIN)
#define FT_ULONG_MIN   (FT_UINT_32_MIN)
#define FT_ULLONG_MIN  (FT_UINT_64_MIN)

#define FT_UCHAR_MAX   (FT_UINT_8_MAX)
#define FT_USHORT_MAX  (FT_UINT_16_MAX)
#define FT_UINT_MAX    (FT_UINT_32_MAX)
#define FT_ULONG_MAX   (FT_UINT_32_MAX)
#define FT_ULLONG_MAX  (FT_UINT_64_MAX)


#define FT_WCHAR_MIN   (FT_UINT_32_MIN)
#define FT_WCHAR_MAX   (FT_UINT_32_MAX)

#define FT_SIZE_MIN    (FT_UINT_64_MIN)
#define FT_SIZE_MAX    (FT_UINT_64_MAX)
#define FT_SSIZE_MIN   (FT_INT_64_MIN)
#define FT_SSIZE_MAX   (FT_INT_64_MAX)

#define FT_PTR_MIN     (FT_UINT_64_MIN)
#define FT_PTR_MAX     (FT_UINT_64_MAX)
#define FT_PTRDIFF_MIN (FT_INT_64_MIN)
#define FT_PTRDIFF_MAX (FT_INT_64_MAX)

#endif
