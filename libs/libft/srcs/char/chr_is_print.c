#include "ft_char.h"

// Function --------------------------------------------------------------------
t_bool
ft_chr_is_print(
	t_char _chr
)
{
	return (32 <= _chr && _chr <= 126);
}
