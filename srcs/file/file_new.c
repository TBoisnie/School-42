#include <stdlib.h>
#include "libft/incs/ft_string.h"
#include "libft/incs/ft_system.h"
#include "ft_ls.h"

t_file *
file_new(
	t_char const * _fullpath
)
{
	t_file * file = malloc(sizeof(t_file));

	if (!file)
	{
		show_error("cannot allocate memory (file_new:malloc)", nullptr, true);
		ft_exit(FT_LS_EXIT_ERR_MAJOR);
	}

	ft_str_copy(_fullpath, file->fullpath);

	if (!file_init(file))
	{
		free(file);
		file = nullptr;
	}

	return (file);
}
