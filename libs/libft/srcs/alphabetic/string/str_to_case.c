#include "libft.h"

// Function --------------------------------------------------------------------
t_char *
ft_str_to_lower(
	t_char * _str
)
{
	t_char * cursor = --_str;

	while (*++cursor)
		*cursor = ft_chr_to_lower(*cursor);

	return (_str);
}

t_char *
ft_str_to_upper(
	t_char * _str
)
{
	t_char * cursor = --_str;

	while (*++cursor)
		*cursor = ft_chr_to_upper(*cursor);

	return (_str);
}
