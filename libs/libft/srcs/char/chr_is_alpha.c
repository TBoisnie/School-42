#include "ft_char.h"

// Function --------------------------------------------------------------------
t_bool
ft_chr_is_alpha(
	t_char _chr
)
{
	return (('a' <= _chr && _chr <= 'z') ||('A' <= _chr && _chr <= 'Z'));
}
