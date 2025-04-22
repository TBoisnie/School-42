#include "libft.h"

// Function --------------------------------------------------------------------
t_char *
ft_str_reverse(
	t_char * _str
)
{
	return (ft_mem_reverse(_str, ft_str_length(_str)));
}
