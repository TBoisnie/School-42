#include "ft_math.h"
#include "ft_memory.h"
#include "ft_string.h"

// Function --------------------------------------------------------------------
t_char *
ft_str_concat(
	t_char * _dst,
	t_char const * _src
)
{
	return (ft_str_concat_limit(_dst, _src, -1));
}

t_char *
ft_str_concat_limit(
	t_char * _dst,
	t_char const * _src,
	t_size _limit
)
{
	t_size dst_len = ft_str_length(_dst);

	if (_limit <= dst_len)
		return (_dst);

	_limit -= dst_len;

	t_size src_len = ft_str_length(_src);
	src_len = FT_MATH_MIN(_limit, src_len);

	ft_mem_concat(_dst, _src, dst_len, src_len);

	_dst[dst_len + src_len] = '\0';

	return (_dst);
}
