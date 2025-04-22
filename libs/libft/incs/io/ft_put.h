#ifndef LIBFT_IO_PUT_H
#define LIBFT_IO_PUT_H

#include <stdarg.h>
#include "../core/ft_types.h"

// Define ----------------------------------------------------------------------
#ifdef FT_IO_FORMAT_BUFFER_SIZE
	#if FT_IO_FORMAT_BUFFER_SIZE <= 1
		#warning __FILE__":"__LINE__": Invalid FT_IO_FORMAT_BUFFER_SIZE (must be > 1), will use default value."
		#undef FT_IO_FORMAT_BUFFER_SIZE
	#endif
#endif

#ifndef FT_IO_FORMAT_BUFFER_SIZE
	#define FT_IO_FORMAT_BUFFER_SIZE  4096
#endif

// Alias -----------------------------------------------------------------------
#define ft_io_out_chr(args...)     ft_io_put_chr(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_str(args...)     ft_io_put_str(FT_IO_CONSOLE_FD_OUT, args)

#define ft_io_out_format(args...)  ft_io_put_format(FT_IO_CONSOLE_FD_OUT, args)

#define ft_io_out_int_8(args...)   ft_io_put_int_8(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_int_16(args...)  ft_io_put_int_16(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_int_32(args...)  ft_io_put_int_32(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_int_64(args...)  ft_io_put_int_64(FT_IO_CONSOLE_FD_OUT, args)

#define ft_io_out_uint_8(args...)   ft_io_put_uint_8(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_uint_16(args...)  ft_io_put_uint_16(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_uint_32(args...)  ft_io_put_uint_32(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_uint_64(args...)  ft_io_put_uint_64(FT_IO_CONSOLE_FD_OUT, args)

#define ft_io_out_int_8_base(args...)   ft_io_put_int_8_base(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_int_16_base(args...)  ft_io_put_int_16_base(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_int_32_base(args...)  ft_io_put_int_32_base(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_int_64_base(args...)  ft_io_put_int_64_base(FT_IO_CONSOLE_FD_OUT, args)

#define ft_io_out_uint_8_base(args...)   ft_io_put_uint_8_base(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_uint_16_base(args...)  ft_io_put_uint_16_base(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_uint_32_base(args...)  ft_io_put_uint_32_base(FT_IO_CONSOLE_FD_OUT, args)
#define ft_io_out_uint_64_base(args...)  ft_io_put_uint_64_base(FT_IO_CONSOLE_FD_OUT, args)

#define ft_io_err_chr(args...)     ft_io_put_chr(FT_IO_CONSOLE_FD_ERR args)
#define ft_io_err_str(args...)     ft_io_put_str(FT_IO_CONSOLE_FD_ERR, args)

#define ft_io_err_format(args...)  ft_io_put_format(FT_IO_CONSOLE_FD_ERR, args)

#define ft_io_err_int_8(args...)   ft_io_put_int_8(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_int_16(args...)  ft_io_put_int_16(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_int_32(args...)  ft_io_put_int_32(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_int_64(args...)  ft_io_put_int_64(FT_IO_CONSOLE_FD_ERR, args)

#define ft_io_err_uint_8(args...)   ft_io_put_uint_8(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_uint_16(args...)  ft_io_put_uint_16(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_uint_32(args...)  ft_io_put_uint_32(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_uint_64(args...)  ft_io_put_uint_64(FT_IO_CONSOLE_FD_ERR, args)

#define ft_io_err_int_8_base(args...)   ft_io_put_int_8_base(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_int_16_base(args...)  ft_io_put_int_16_base(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_int_32_base(args...)  ft_io_put_int_32_base(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_int_64_base(args...)  ft_io_put_int_64_base(FT_IO_CONSOLE_FD_ERR, args)

#define ft_io_err_uint_8_base(args...)   ft_io_put_uint_8_base(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_uint_16_base(args...)  ft_io_put_uint_16_base(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_uint_32_base(args...)  ft_io_put_uint_32_base(FT_IO_CONSOLE_FD_ERR, args)
#define ft_io_err_uint_64_base(args...)  ft_io_put_uint_64_base(FT_IO_CONSOLE_FD_ERR, args)

// Function --------------------------------------------------------------------
/**
 * Write a character on a file descriptor.
 *
 * @param _fd: File descriptor to write on
 * @param _chr: Character to write
**/
t_void ft_io_put_chr(t_fd _fd, t_char _chr);

/**
 * Write a string on a file descriptor.
 *
 * @param _fd: File descriptor to write on
 * @param _str: String to write
**/
t_void ft_io_put_str(t_fd _fd, t_char const * _str);

/**
 * Format a string then write it on a file descriptor.
 *
 * @param _fd: File descriptor to write on
 * @param _fmt: String to format
 * @param ...: Arguments used to format
 *
 * @return Size of the formatted string
**/
t_size ft_io_put_format(t_fd _fd, t_char const * _fmt, ...);

/**
 * Write an integer on a file descriptor (using base).
 *
 * @param _fd: File descriptor to write on
 * @param _int: Integer to write
 * @param _base: Base to convert
**/
t_void ft_io_put_int_8(t_fd _fd, t_int_8 _int);
t_void ft_io_put_int_16(t_fd _fd, t_int_16 _int);
t_void ft_io_put_int_32(t_fd _fd, t_int_32 _int);
t_void ft_io_put_int_64(t_fd _fd, t_int_64 _int);

t_void ft_io_put_uint_8(t_fd _fd, t_uint_8 _uint);
t_void ft_io_put_uint_16(t_fd _fd, t_uint_16 _uint);
t_void ft_io_put_uint_32(t_fd _fd, t_uint_32 _uint);
t_void ft_io_put_uint_64(t_fd _fd, t_uint_64 _uint);

t_void ft_io_put_int_8_base(t_fd _fd, t_int_8 _int, t_char const * const _base);
t_void ft_io_put_int_16_base(t_fd _fd, t_int_16 _int, t_char const * const _base);
t_void ft_io_put_int_32_base(t_fd _fd, t_int_32 _int, t_char const * const _base);
t_void ft_io_put_int_64_base(t_fd _fd, t_int_64 _int, t_char const * const _base);

t_void ft_io_put_uint_8_base(t_fd _fd, t_uint_8 _uint, t_char const * const _base);
t_void ft_io_put_uint_16_base(t_fd _fd, t_uint_16 _uint, t_char const * const _base);
t_void ft_io_put_uint_32_base(t_fd _fd, t_uint_32 _uint, t_char const * const _base);
t_void ft_io_put_uint_64_base(t_fd _fd, t_uint_64 _uint, t_char const * const _base);

#endif
