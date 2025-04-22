#include "libft/incs/ft_string.h"
#include "ft_ls.h"

t_ssize
compare_by_size(
	t_void const * _file_1,
	t_void const * _file_2
)
{

	t_file const * file_1 = _file_1;
	t_file const * file_2 = _file_2;

	t_ssize diff = file_2->stats.st_size - file_1->stats.st_size;

	if (diff)
		return (diff);

	return (compare_by_name(file_1, file_2));
}
