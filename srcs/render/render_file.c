#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include "libft/incs/ft_io.h"
#include "libft/incs/ft_limits.h"
#include "libft/incs/ft_memory.h"
#include "libft/incs/ft_number.h"
#include "libft/incs/ft_string.h"
#include "libft/incs/ft_system.h"
#include "ft_ls.h"

static t_void
get_color(
	struct stat const * stats_file,
	struct stat const * stats_target,
	t_char color[16]
)
{
	t_char const * c = "";

	if (FT_MEM_BIT_ISSET(stats_file->st_mode, S_ISUID))
		c = "\033[37;41m";
	else if (FT_MEM_BIT_ISSET(stats_file->st_mode, S_ISGID))
		c = "\033[30;43m";
	else
	{
		if (S_ISREG(stats_file->st_mode))
		{
			if (FT_MEM_BIT_ISSET(stats_file->st_mode, S_IXUSR))
				c = "\033[01;32m";
		}
		if (S_ISDIR(stats_file->st_mode))
		{
			c = "\033[01;34m";

			if (FT_MEM_BIT_ISSET(stats_file->st_mode, S_ISVTX))
			{
				c = "\033[37;44m";

				if (FT_MEM_BIT_ISSET(stats_file->st_mode, S_IWOTH))
					c = "\033[30;42m";
			}
			else if (FT_MEM_BIT_ISSET(stats_file->st_mode, S_IWOTH))
				c = "\033[34;42m";
		}
		else if (S_ISLNK(stats_file->st_mode))
		{
			c = "\033[01;36m";

			if (!stats_target)
				c = "\033[40;31;01m";
		}
		else if (S_ISCHR(stats_file->st_mode))
			c = "\033[40;33;01m";
		else if (S_ISBLK(stats_file->st_mode))
			c = "\033[40;33;01m";
		else if (S_ISFIFO(stats_file->st_mode))
			c = "\033[40;33m";
		else if (S_ISSOCK(stats_file->st_mode))
			c = "\033[01;35m";
	}

	ft_str_copy(c, color);
}

t_void
render_file(
	t_file const * _file,
	t_ls const * _ls,
	t_bool _force_show
)
{
	if (_file->name[0] == '.' && !FT_MEM_BIT_ISSET(_ls->options, SHOW_ALL) && !_force_show)
		return;

	t_char buffer[32] = { 0 };

	// Colors
	t_char color_file[16] = "";
	t_char color_target[16] = "";

	if (FT_MEM_BIT_ISSET(_ls->options, COLOR))
	{
		if (S_ISLNK(_file->stats.st_mode))
		{
			t_char target[FT_PATH_MAX] = "";

			if (_file->target[0] != '/')
			{
				t_char * path = ft_str_rfind_chr(_file->fullpath, '/');
				if (path)
					ft_str_copy_limit(_file->fullpath, target, path - _file->fullpath + 1);
			}
			ft_str_concat(target, _file->target);

			struct stat stat_target;
			if (stat(target, &stat_target) == 0)
			{
				get_color(&stat_target, &stat_target, color_target);
				get_color(&_file->stats, &stat_target, color_file);
			}
			else
				get_color(&_file->stats, nullptr, color_file);
		}
		else
			get_color(&_file->stats, nullptr, color_file);
	}

	if (FT_MEM_BIT_ISSET(_ls->options, SHOW_INODE))
	{
		ft_printf(
			"%*lu ",
			(FT_MEM_BIT_ISSET(_ls->options, FORMAT_LONG) ||  FT_MEM_BIT_ISSET(_ls->options, SHOW_BLOCKS))
				? _ls->columns.inode
				: 0,
			_file->stats.st_ino
		);
	}

	if (FT_MEM_BIT_ISSET(_ls->options, SHOW_BLOCKS))
	{
		ft_printf(
			"%*lu ",
			_ls->columns.blocks,
			(_file->stats.st_blocks + 1) / 2
		);
	}

	if (FT_MEM_BIT_ISSET(_ls->options, FORMAT_LONG))
	{
		ft_printf(
			"%c%c%c%c%c%c%c%c%c%c %*lu ",
			// Type
			S_ISBLK (_file->stats.st_mode) ? 'b' :
			S_ISCHR (_file->stats.st_mode) ? 'c' :
			S_ISDIR (_file->stats.st_mode) ? 'd' :
			S_ISFIFO(_file->stats.st_mode) ? 'p' :
			S_ISLNK (_file->stats.st_mode) ? 'l' :
			S_ISSOCK(_file->stats.st_mode) ? 's' :
			S_ISREG (_file->stats.st_mode) ? '-' : '?',
			// Rights
			FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IRUSR) ? 'r' : '-',
			FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IWUSR) ? 'w' : '-',
			FT_MEM_BIT_ISSET(_file->stats.st_mode, S_ISUID)
				? FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IXUSR) ? 's' : 'S'
				: FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IXUSR) ? 'x' : '-',

			FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IRGRP) ? 'r' : '-',
			FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IWGRP) ? 'w' : '-',
			FT_MEM_BIT_ISSET(_file->stats.st_mode, S_ISGID)
				? FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IXGRP) ? 's' : 'S'
				: FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IXGRP) ? 'x' : '-',

			FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IROTH) ? 'r' : '-',
			FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IWOTH) ? 'w' : '-',
			FT_MEM_BIT_ISSET(_file->stats.st_mode, S_ISVTX)
				? FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IXOTH) ? 't' : 'T'
				: FT_MEM_BIT_ISSET(_file->stats.st_mode, S_IXOTH) ? 'x' : '-',
			// Links
			_ls->columns.links,
			_file->stats.st_nlink
		);

		// Owner (User)
		if (!FT_MEM_BIT_ISSET(_ls->options, HIDE_USER))
		{
			if (FT_MEM_BIT_ISSET(_ls->options, OWNERS_NUM) || _file->user_name[0] == '\0')
			{
				ft_uint_to_str(_file->user_id, buffer);
				ft_printf("%*s ", _ls->columns.user, buffer);
			}
			else
			{
				ft_printf("%-*s ", _ls->columns.user, _file->user_name);
			}
		}

		// Owner (Group)
		if (!FT_MEM_BIT_ISSET(_ls->options, HIDE_GROUP))
		{
			if (FT_MEM_BIT_ISSET(_ls->options, OWNERS_NUM) || _file->group_name[0] == '\0')
			{
				ft_uint_to_str(_file->group_id, buffer);
				ft_printf("%*s ", _ls->columns.group, buffer);
			}
			else
			{
				ft_printf("%-*s ", _ls->columns.group, _file->group_name);
			}
		}

		// Size
		if (S_ISCHR(_file->stats.st_mode) || S_ISBLK(_file->stats.st_mode))
		{
			ft_printf(
				"%*ld, %*ld ",
				_ls->columns.size - _ls->columns.minor - 2,
				FT_DEVICE_MAJOR(_file->stats.st_rdev),
				_ls->columns.minor,
				FT_DEVICE_MINOR(_file->stats.st_rdev)
			);
		}
		else
		{
			ft_printf("%*ld ", _ls->columns.size, (t_long)_file->stats.st_size);
		}

		// Date
		t_long show_time =
			FT_MEM_BIT_ISSET(_ls->options, USE_ATIME) ?
				_file->stats.st_atim.tv_sec :
			FT_MEM_BIT_ISSET(_ls->options, USE_CTIME) ?
				_file->stats.st_ctim.tv_sec :
			_file->stats.st_mtim.tv_sec
		;

		t_bool is_too_old = ((time(nullptr) - show_time) > FT_LS_DATE_LIMIT_IN_SECONDS);

		ft_printf(
			"%*.*s %*.*s ",
			_ls->columns.date,
			6,
			ctime(&show_time) + 4,
			_ls->columns.time,
			(is_too_old) ? 4 : 5,
			ctime(&show_time) + (is_too_old ? 20 : 11)
		);
	}

	ft_printf(
		"%s%s%s",
		color_file,
		(_force_show) ? _file->fullpath : _file->name,
		(*color_file != '\0') ? "\033[0m" : ""
	);

	if (FT_MEM_BIT_ISSET(_ls->options, DIR_SUFFIX) && S_ISDIR(_file->stats.st_mode))
	{
		ft_printf("/");
	}

	if (FT_MEM_BIT_ISSET(_ls->options, FORMAT_LONG))
	{
		if (S_ISLNK(_file->stats.st_mode))
		{
			ft_printf(
				" -> %s%s%s",
				color_target,
				_file->target,
				(*color_target != '\0') ? "\033[0m" : ""
			);
		}
	}

	ft_printf("%c", FT_MEM_BIT_ISSET(_ls->options, ZERO_END) ? '\0' : '\n');
}
