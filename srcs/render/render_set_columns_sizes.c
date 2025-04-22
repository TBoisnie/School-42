#include "libft/incs/ft_math.h"
#include "libft/incs/ft_memory.h"
#include "libft/incs/ft_number.h"
#include "libft/incs/ft_string.h"
#include "libft/incs/ft_system.h"
#include "ft_ls.h"

t_void
render_set_columns_sizes(
	t_file const * _file,
	t_ls * _ls
)
{
	t_char const * name;
	t_char buffer[32];
	t_uint length = 0;

	// Inode
	ft_ulong_to_str(_file->stats.st_ino, buffer);
	length = ft_str_length(buffer);
	_ls->columns.inode = FT_MATH_MAX(_ls->columns.inode, length);

	// Blocks
	ft_long_to_str((_file->stats.st_blocks + 1) / 2, buffer);
	length = ft_str_length(buffer);
	_ls->columns.blocks = FT_MATH_MAX(_ls->columns.blocks, length);

	// Links
	ft_ulong_to_str(_file->stats.st_nlink, buffer);
	length = ft_str_length(buffer);
	_ls->columns.links = FT_MATH_MAX(_ls->columns.links, length);

	// Owner (User)
	name = _file->user_name;
	if (FT_MEM_BIT_ISSET(_ls->options, OWNERS_NUM) || name[0] == '\0')
	{
		ft_uint_to_str(_file->user_id, buffer);
		name = buffer;
	}
	length = ft_str_length(name);
	_ls->columns.user = FT_MATH_MAX(_ls->columns.user, length);

	// Owner (Group)
	name = _file->group_name;
	if (FT_MEM_BIT_ISSET(_ls->options, OWNERS_NUM) || name[0] == '\0')
	{
		ft_uint_to_str(_file->group_id, buffer);
		name = buffer;
	}
	length = ft_str_length(name);
	_ls->columns.group = FT_MATH_MAX(_ls->columns.group, length);

	// Size
	if (S_ISCHR(_file->stats.st_mode) || S_ISBLK(_file->stats.st_mode))
	{
		ft_uint_to_str(FT_DEVICE_MAJOR(_file->stats.st_rdev), buffer);
		length = ft_str_length(buffer);
		_ls->columns.major = FT_MATH_MAX(_ls->columns.major, length);

		ft_uint_to_str(FT_DEVICE_MINOR(_file->stats.st_rdev), buffer);
		length = ft_str_length(buffer);
		_ls->columns.minor = FT_MATH_MAX(_ls->columns.minor, length);
	}

	ft_long_to_str(_file->stats.st_size, buffer);
	length = ft_str_length(buffer);
	_ls->columns.size = FT_MATH_MAX(_ls->columns.size, length);

	if ((_ls->columns.major + _ls->columns.minor) != 0)
	{
		_ls->columns.size = FT_MATH_MAX(_ls->columns.size, _ls->columns.major + _ls->columns.minor + 2); // +2 because of formatting (%*ld, %*ld)
	}

	// Date
	_ls->columns.date = 6;
	// Time
	_ls->columns.time = 5;
}
