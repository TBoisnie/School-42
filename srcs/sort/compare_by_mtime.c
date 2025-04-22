#include "ft_ls.h"

t_ssize
compare_by_mtime(
	t_void const * _file_1,
	t_void const * _file_2
)
{
	t_file const * file_1 = _file_1;
	t_file const * file_2 = _file_2;

	t_ssize diff;

	diff = file_2->stats.st_mtim.tv_sec - file_1->stats.st_mtim.tv_sec;

	if (diff != 0)
		return (diff);

	diff = file_2->stats.st_mtim.tv_nsec - file_1->stats.st_mtim.tv_nsec;

	if (diff != 0)
		return (diff);

	return (compare_by_name(file_1, file_2));
}
