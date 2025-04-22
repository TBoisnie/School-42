#include "ft_char.h"

// Function --------------------------------------------------------------------
t_bool
ft_chr_is_ascii(
	t_char _chr
)
{
	return (0 <= _chr && _chr <= 127);
}
