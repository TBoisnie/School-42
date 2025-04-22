#ifndef LIBFT_IO_H
#define LIBFT_IO_H

#include <stdarg.h>
#include "ft_types.h"

// Define ----------------------------------------------------------------------
#ifdef FT_GNL_BUFFER_SIZE
#if     FT_GNL_BUFFER_SIZE <= 1
# warning __FILE__":"__LINE__": Invalid FT_GNL_BUFFER_SIZE (must be > 1), will use default value."
# undef FT_GNL_BUFFER_SIZE
#endif
#endif

#ifndef FT_GNL_BUFFER_SIZE
#define FT_GNL_BUFFER_SIZE (4096)
#endif

#ifdef FT_PRINTF_BUFFER_SIZE
#if     FT_PRINTF_BUFFER_SIZE <= 1
# warning __FILE__":"__LINE__": Invalid FT_PRINTF_BUFFER_SIZE (must be > 1), will use default value."
# undef FT_PRINTF_BUFFER_SIZE
#endif
#endif

#ifndef FT_PRINTF_BUFFER_SIZE
#define FT_PRINTF_BUFFER_SIZE (4096)
#endif

// Function --------------------------------------------------------------------
t_void ft_fd_put_chr(t_fd _fd, t_char _chr);
t_void ft_fd_put_str(t_fd _fd, t_char const * _str);
t_void ft_fd_put_signed(t_fd _fd, t_llong _nbr);
t_void ft_fd_put_signed_base(t_fd _fd, t_llong _nbr, t_char const * const _base);
t_void ft_fd_put_unsigned(t_fd _fd, t_ullong _nbr);
t_void ft_fd_put_unsigned_base(t_fd _fd, t_ullong _nbr, t_char const * const _base);

t_size ft_printf(t_char const * _fmt, ...);
t_size ft_fprintf(t_fd _fd, t_char const * _fmt, ...);

t_ssize ft_get_next_line(t_fd _fd, t_char ** _line);

#endif
