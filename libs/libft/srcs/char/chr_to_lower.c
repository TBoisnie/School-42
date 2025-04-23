#include "ft_char.h"

// Function --------------------------------------------------------------------
t_char
ft_chr_to_lower(
	t_char _chr
)
{
	return (_chr - ('A' - 'a') * ('A' <= _chr && _chr <= 'Z'));
}
