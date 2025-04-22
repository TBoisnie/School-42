#include "libft.h"

// Declaration -----------------------------------------------------------------
static t_char * _str_find_str(t_char const * _haystack, t_char const * _needle, t_size _needle_len);
static t_char * _str_rfind_str(t_char const * _haystack, t_char const * _needle, t_size _needle_len);

// Function --------------------------------------------------------------------
t_char *
ft_str_find_chr(
	t_char const * _haystack,
	t_char const _needle
)
{
	return (_str_find_str(_haystack, (t_char const[2]){ _needle, '\0' }, 1));
}

t_char *
ft_str_find_str(
	t_char const * _haystack,
	t_char const * _needle
)
{
	return (_str_find_str(_haystack, _needle, ft_str_length(_needle)));
}

t_char *
ft_str_rfind_chr(
	t_char const * _haystack,
	t_char const _needle
)
{
	return (_str_rfind_str(_haystack, (t_char const[2]){ _needle, '\0' }, 1));
}

t_char *
ft_str_rfind_str(
	t_char const * _haystack,
	t_char const * _needle
)
{
	return (_str_rfind_str(_haystack, _needle, ft_str_length(_needle)));
}

// Static ----------------------------------------------------------------------
static t_char *
_str_find_str(
	t_char const * _haystack,
	t_char const * _needle,
	t_size _needle_len
)
{
	if (!_haystack || !_needle)
		return (nullptr);

	while (*_haystack)
	{
		if (ft_mem_compare(_haystack, _needle, _needle_len) == 0)
			return ((t_char *) _haystack);

		_haystack++;
	}

	return (nullptr);
}

static t_char *
_str_rfind_str(
	t_char const * _haystack,
	t_char const * _needle,
	t_size _needle_len
)
{
	t_char const * last = nullptr;
	t_char const * found = nullptr;

	while ((found = _str_find_str(_haystack, _needle, _needle_len)))
	{
		last = found;
		_haystack = ++found;
	}

	return ((t_char *) last);
}
