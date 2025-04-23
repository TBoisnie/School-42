#include "ft_char.h"
#include "ft_string.h"

// Function --------------------------------------------------------------------
t_int
ft_str_compare(
	t_char const * _str_1,
	t_char const * _str_2
)
{
	return (ft_str_compare_limit(_str_1, _str_2, -1));
}

t_int
ft_str_compare_limit(
	t_char const * _str_1,
	t_char const * _str_2,
	t_size const _limit
)
{
	t_size i;

	for (i = 0; i < _limit; i++)
	{
		if (
			_str_1[i] == '\0' ||
			_str_2[i] == '\0' ||
			_str_1[i] != _str_2[i]
		)
			break;
	}

	return (_str_1[i] - _str_2[i]);
}

t_int
ft_str_icompare(
	t_char const * _str_1,
	t_char const * _str_2
)
{
	return (ft_str_icompare_limit(_str_1, _str_2, -1));
}

t_int
ft_str_icompare_limit(
	t_char const * _str_1,
	t_char const * _str_2,
	t_size _limit
)
{
	t_size i;

	for (i = 0; i < _limit ; i++)
	{
		if (
			_str_1[i] == '\0' ||
			_str_2[i] == '\0' ||
			ft_chr_to_lower(_str_1[i]) != ft_chr_to_lower(_str_2[i])
		)
			break;
	}

	return (ft_chr_to_lower(_str_1[i]) - ft_chr_to_lower(_str_2[i]));
}
