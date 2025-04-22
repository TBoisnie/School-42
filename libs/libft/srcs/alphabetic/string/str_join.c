#include "libft.h"

// Function --------------------------------------------------------------------
t_char *
ft_str_join(
	t_char const * _str_1,
	t_char const * _str_2
)
{
	return (ft_mem_join(_str_1, _str_2, ft_str_length(_str_1), ft_str_length(_str_2) + 1));
}
