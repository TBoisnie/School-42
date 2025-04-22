#include "libft.h"

// Function --------------------------------------------------------------------
t_bool
ft_chr_is_alnum(
	t_char _chr
)
{
	return (ft_chr_is_alpha(_chr) || ft_chr_is_digit(_chr));
}

t_bool
ft_chr_is_alpha(
	t_char _chr
)
{
	return (('a' <= _chr && _chr <= 'z') ||('A' <= _chr && _chr <= 'Z'));
}

t_bool
ft_chr_is_ascii(
	t_char _chr
)
{
	return (0 <= _chr /*&& _chr <= 127*/);
}

t_bool
ft_chr_is_blank(
	t_char _chr
)
{
	return (_chr == ' ' || _chr == '\t');
}

t_bool
ft_chr_is_digit(
	t_char _chr
)
{
	return ('0' <= _chr && _chr <= '9');
}

t_bool
ft_chr_is_hex(
	t_char _chr
)
{
	return (
		('0' <= _chr && _chr <= '9') ||
		('a' <= _chr && _chr <= 'f') ||
		('A' <= _chr && _chr <= 'F')
	);
}

t_bool
ft_chr_is_print(
	t_char _chr
)
{
	return (32 <= _chr && _chr <= 126);
}

t_bool
ft_chr_is_space(
	t_char _chr
)
{
	return (
		_chr == ' '  || _chr == '\t' || _chr == '\n' ||
		_chr == '\v' || _chr == '\f' || _chr == '\r'
	);
}
