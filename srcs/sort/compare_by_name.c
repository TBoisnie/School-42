#include "libft/incs/ft_string.h"
#include "ft_ls.h"

t_ssize
compare_by_name(
	t_void const * _file_1,
	t_void const * _file_2
)
{
	t_char * name_1 = ((t_file *)_file_1)->fullpath;
	t_char * name_2 = ((t_file *)_file_2)->fullpath;

	return (ft_str_compare(name_1, name_2));
}
