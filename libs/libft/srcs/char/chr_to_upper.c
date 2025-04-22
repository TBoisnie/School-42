#include "ft_char.h"

// Function --------------------------------------------------------------------
t_char
ft_chr_to_upper(
	t_char _chr
)
{
	return (_chr + ('A' - 'a') * ('a' <= _chr && _chr <= 'z'));
}
