#include "ft_char.h"

// Function --------------------------------------------------------------------
t_bool
ft_chr_is_space(
	t_char _chr
)
{
	return (
		_chr == ' '  || _chr == '\t' || _chr == '\n' ||
		_chr == '\v' || _chr == '\f' || _chr == '\r'
	);
}
