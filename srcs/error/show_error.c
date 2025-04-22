#include <errno.h>
#include <string.h>
#include "libft/incs/ft_io.h"
#include "libft/incs/ft_console.h"
#include "ft_ls.h"

t_void
show_error(
	t_char const * _message,
	t_char const * _detail,
	t_bool _show_errno
)
{
	ft_fprintf(
		FT_CONSOLE_FD_ERR,
		"ls: %s%s%s%s%s%s\n",
		_message,
		(_detail) ? " '" : "",
		(_detail) ? _detail : "",
		(_detail) ? "'" : "",
		(_show_errno) ? ": " : "",
		(_show_errno) ? strerror(errno) : ""
	);
}
