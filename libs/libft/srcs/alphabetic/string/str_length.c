#include "libft.h"

// Function --------------------------------------------------------------------
t_size
ft_str_length(
	t_char const * _str
)
{
	if (!_str)
		return (0);

	t_char const * end = _str;

	while (*end++)
		;

	return (end - _str - 1);
}
