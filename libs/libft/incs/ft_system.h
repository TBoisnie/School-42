#ifndef LIBFT_SYSTEM_H
#define LIBFT_SYSTEM_H

#include "ft_types.h"

// Define ----------------------------------------------------------------------
#define FT_EXIT_OK  (0)
#define FT_EXIT_ERR (1)

#define FT_DEVICE_MAJOR(dev) (((dev) & 0xfff00) >> 8)
#define FT_DEVICE_MINOR(dev) (((dev) & 0xff) | (((dev) >> 12) & 0xfff00))

// Function --------------------------------------------------------------------
t_void ft_exit(t_int _code);
t_void ft_exit_message(t_int _code, t_char const * _message);

#endif
