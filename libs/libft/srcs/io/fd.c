#include <unistd.h>
#include "ft_io.h"
#include "ft_number.h"
#include "ft_string.h"

// Function --------------------------------------------------------------------
t_void
ft_fd_put_chr(
	t_fd _fd,
	t_char _chr
)
{
	write(_fd, &_chr, 1);
}

t_void
ft_fd_put_str(
	t_fd _fd,
	t_char const * _str
)
{
	write(_fd, _str, ft_str_length(_str));
}

t_void
ft_fd_put_signed(
	t_fd _fd,
	t_llong _nbr
)
{
	ft_fd_put_signed_base(_fd, _nbr, FT_NBR_BASE_DEC);
}

t_void
ft_fd_put_signed_base(
	t_fd _fd,
	t_llong _nbr,
	t_char const * const _base
)
{
	t_char buffer[64 + 2]; // +1 for sign, +1 for \0

	ft_llong_to_str_base(_nbr, buffer, _base);

	ft_fd_put_str(_fd, buffer);
}

t_void
ft_fd_put_unsigned(
	t_fd _fd,
	t_ullong _nbr
)
{
	ft_fd_put_unsigned_base(_fd, _nbr, FT_NBR_BASE_DEC);
}

t_void
ft_fd_put_unsigned_base(
	t_fd _fd,
	t_ullong _nbr,
	t_char const * const _base
)
{
	t_char buffer[64 + 2]; // +1 for sign, +1 for \0

	ft_ullong_to_str_base(_nbr, buffer, _base);

	ft_fd_put_str(_fd, buffer);
}
