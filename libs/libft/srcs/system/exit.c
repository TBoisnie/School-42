#include <stdlib.h>
#include "ft_console.h"
#include "ft_io.h"
#include "ft_system.h"

// Function --------------------------------------------------------------------
t_void
ft_exit(
	t_int const _code
)
{
	exit(_code);
}

t_void
ft_exit_message(
	t_int const _code,
	t_char const * _message
)
{
	t_fd fd = (_code == FT_EXIT_OK)
		? FT_CONSOLE_FD_OUT
		: FT_CONSOLE_FD_ERR
	;

	ft_fprintf(fd, "%s\n", _message);

	exit(_code);
}
