#include "ft_char.h"

// Function --------------------------------------------------------------------
t_bool
ft_chr_is_blank(
	t_char _chr
)
{
	return (_chr == ' ' || _chr == '\t');
}
