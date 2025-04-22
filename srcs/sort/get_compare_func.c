#include "libft/incs/ft_memory.h"
#include "ft_ls.h"

t_list_func_cmp
get_compare_func(
	t_ls const * _ls
)
{
	if (FT_MEM_BIT_ISSET(_ls->options, SORT_SIZE))
		return compare_by_size;

	if (FT_MEM_BIT_ISSET(_ls->options, USE_ATIME))
	{
		if (
			FT_MEM_BIT_ISSET(_ls->options, FORMAT_LONG) &&
			!FT_MEM_BIT_ISSET(_ls->options, SORT_TIME)
		)
			return compare_by_name;

		return compare_by_atime;
	}

	if (FT_MEM_BIT_ISSET(_ls->options, USE_CTIME))
	{
		if (
			FT_MEM_BIT_ISSET(_ls->options, FORMAT_LONG) &&
			!FT_MEM_BIT_ISSET(_ls->options, SORT_TIME)
		)
			return compare_by_name;

		return compare_by_ctime;
	}

	if (FT_MEM_BIT_ISSET(_ls->options, SORT_TIME))
		return compare_by_mtime;

	return compare_by_name;
}
