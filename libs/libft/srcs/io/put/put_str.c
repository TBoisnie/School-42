#include <unistd.h>
#include "libft.h"

// Function --------------------------------------------------------------------
t_void
ft_io_put_chr(
	t_fd _fd,
	t_char _chr
)
{
	write(_fd, &_chr, 1);
}

t_void
ft_io_put_str(
	t_fd _fd,
	t_char const * _str
)
{
	write(_fd, _str, ft_str_length(_str));
}
