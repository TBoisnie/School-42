#include "ft_char.h"

// Function --------------------------------------------------------------------
t_bool
ft_chr_is_alnum(
	t_char _chr
)
{
	return (ft_chr_is_alpha(_chr) || ft_chr_is_digit(_chr));
}
