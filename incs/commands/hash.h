#ifndef FT_SSL_COMMANDS_HASH_H
#define FT_SSL_COMMANDS_HASH_H

#include "libft/incs/libft.h"

// Function --------------------------------------------------------------------
t_int cmd_md5(t_uint _argc, t_char const * _argv[]);
t_int cmd_sha256(t_uint _argc, t_char const * _argv[]);
t_int cmd_whirlpool(t_uint _argc, t_char const * _argv[]);

#endif
