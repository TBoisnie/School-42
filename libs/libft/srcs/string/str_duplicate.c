#include <stdlib.h>
#include "ft_memory.h"
#include "ft_string.h"

// Function --------------------------------------------------------------------
t_char *
ft_str_duplicate(
	t_char const * _str
)
{
	return (ft_str_duplicate_limit(_str, -1));
}

t_char *
ft_str_duplicate_limit(
	t_char const * _str,
	t_size _limit
)
{
	t_size str_len = ft_str_length(_str);

	_limit = (_limit < str_len) ? _limit : str_len;

	t_char * dup = malloc(_limit + 1);

	if (!dup)
		return (nullptr);

	ft_mem_copy(_str, dup, _limit);

	dup[_limit] = '\0';

	return (dup);
}
