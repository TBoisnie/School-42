#include "libft.h"

// Function --------------------------------------------------------------------
t_char *
ft_str_copy(
	t_char const * _src,
	t_char * _dst
)
{
	return (ft_str_copy_limit(_src, _dst, FT_SIZE_MAX));
}

t_char *
ft_str_copy_limit(
	t_char const * _src,
	t_char * _dst,
	t_size _limit
)
{
	t_size src_len = ft_str_length(_src);

	_limit = FT_MATH_MIN(_limit, src_len);

	ft_mem_copy(_src, _dst, _limit);

	_dst[_limit] = '\0';

	return (_dst);
}
