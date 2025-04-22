#include "libft.h"

// Function --------------------------------------------------------------------
t_char *
ft_str_trim(
	t_char * _str,
	t_char const * const _trim
)
{
	t_char * cursor;

	cursor = _str;
	while (ft_str_find_chr(_trim, *cursor))
		++cursor;

	t_size length = ft_str_length(cursor);
	ft_mem_move(cursor, _str, length + 1);

	if (length == 0)
		return (_str);

	cursor = _str + length - 1;
	while (ft_str_find_chr(_trim, *cursor))
		--cursor;

	*++cursor = '\0';

	return (_str);
}
