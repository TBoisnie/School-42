#include "libft.h"

// Function --------------------------------------------------------------------
static t_byte
_hex_to_byte(
	t_char _hex
)
{
	return (
		('a' <= _hex && _hex <= 'f') ? 10 + (_hex - 'a') :
		('A' <= _hex && _hex <= 'F') ? 10 + (_hex - 'A') :
		                                    (_hex - '0')
	);
}

t_byte
ft_mem_hex_to_byte(
	t_char const _hex[2]
)
{
	t_byte left = _hex_to_byte(_hex[0]);
	t_byte right = _hex_to_byte(_hex[1]);

	return ((left << 4) | right);
}
