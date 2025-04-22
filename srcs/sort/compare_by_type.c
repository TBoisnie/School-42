#include "ft_ls.h"

t_ssize
compare_by_type(
	t_void const * _file_1,
	t_void const * _file_2
)
{
	t_file const * file_1 = _file_1;
	t_file const * file_2 = _file_2;

	if (S_ISDIR(file_1->stats.st_mode) && !S_ISDIR(file_2->stats.st_mode))
		return (1);
	if (!S_ISDIR(file_1->stats.st_mode) && S_ISDIR(file_2->stats.st_mode))
		return (-1);

	return (0);
}
