#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/incs/ft_string.h"
#include "libft/incs/ft_system.h"
#include "ft_ls.h"

t_file *
file_init(
	t_file * _file
)
{
	t_char * name = ft_str_rfind_chr(_file->fullpath, '/');

	_file->name = (name) ? ++name : _file->fullpath;

	if (lstat(_file->fullpath, &_file->stats) < 0)
	{
		show_error("cannot access", _file->fullpath, true);
		return (nullptr);
	}

	if (S_ISLNK(_file->stats.st_mode))
	{
		if (readlink(_file->fullpath, _file->target, _file->stats.st_size + 1) < 0)
		{
			show_error("cannot access", nullptr, true);
			return (nullptr);
		}

		_file->target[_file->stats.st_size] = '\0';
	}

	struct passwd * user = getpwuid(_file->stats.st_uid);

	if (!user)
	{
		show_error("cannot get user", nullptr, true);
		return (nullptr);
	}

	ft_str_copy(user->pw_name, _file->user_name);
	_file->user_id = user->pw_uid;

	struct group * group = getgrgid(_file->stats.st_gid);

	if (!group)
	{
		show_error("cannot get group", nullptr, true);
		return (nullptr);
	}

	ft_str_copy(group->gr_name, _file->group_name);
	_file->group_id = group->gr_gid;

	return (_file);
}
