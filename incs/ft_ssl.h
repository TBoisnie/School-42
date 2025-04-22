#ifndef FT_SSL_H
#define FT_SSL_H

#include "libft/incs/libft.h"

// Define ----------------------------------------------------------------------
#define USAGE \
	"usage: ft_ssl command [...flags] [...args]\n" \
	"\n" \
	"Standard commands:\n" \
	"\n" \
	"Message Digest commands:\n" \
	"  md5\n" \
	"  sha256\n" \
	"  whirlpool\n" \
	"\n" \
	"Cypher commands:\n" \
	"\n"

// Typedef ---------------------------------------------------------------------
typedef struct s_command t_command;

// Struct ----------------------------------------------------------------------
struct s_command
{
	t_char const * name;
	t_int (* func) (t_uint _argc, t_char const * _argv[]);
};

// Function --------------------------------------------------------------------

#endif
