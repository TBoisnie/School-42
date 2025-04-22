#include "libft/incs/ft_io.h"
#include "libft/incs/ft_memory.h"
#include "libft/incs/ft_string.h"
#include "libft/incs/ft_system.h"
#include "ft_ls.h"

static t_list *
_load_file_info(
	t_list * _lst,
	t_char const * _path
)
{
	t_file * file = file_new(_path);

	if (!file)
		return (nullptr);

	t_list * front = ft_lst_push_front(_lst, file);

	if (!front)
	{
		show_error("cannot allocate memory (4)", nullptr, true);
		ft_exit(FT_LS_EXIT_ERR_MAJOR);
	}

	return (front);
}

t_void
parse_args(
	t_int _argc,
	t_char * _argv[],
	t_ls * _ls
)
{
	t_bool has_provided_file = false;

	t_int i;
	for (i = 1; i < _argc; i++)
	{
		t_char const * arg = _argv[i];

		// File / Directory
		if (arg[0] != '-')
		{
			has_provided_file = true;

			t_list * front = _load_file_info(_ls->files, arg);

			if (!front)
				_ls->exit_code = FT_LS_EXIT_ERR_MINOR;
			else
				_ls->files = front;

			continue;
		}

		// Option (long)
		if (arg[1] == '-')
		{
			if (ft_str_compare(&arg[2], "help") == 0)
			{
				ft_printf(USAGE);
				ft_exit(FT_EXIT_OK);
			}

			if (ft_str_compare(&arg[2], "color") == 0)
			{
				FT_MEM_BIT_SET(_ls->options, COLOR);
				continue;
			}

			if (ft_str_compare(&arg[2], "zero") == 0)
			{
				FT_MEM_BIT_SET(_ls->options, ZERO_END);
				continue;
			}

			if (ft_str_compare(&arg[2], "all") == 0)
			{
				FT_MEM_BIT_SET(_ls->options, SHOW_ALL);
				continue;
			}

			if (ft_str_compare(&arg[2], "no-group") == 0)
			{
				FT_MEM_BIT_SET(_ls->options, HIDE_GROUP);
				continue;
			}

			if (ft_str_compare(&arg[2], "inode") == 0)
			{
				FT_MEM_BIT_SET(_ls->options, SHOW_INODE);
				continue;
			}

			if (ft_str_compare(&arg[2], "reverse") == 0)
			{
				FT_MEM_BIT_SET(_ls->options, SORT_REVERSE);
				continue;
			}

			if (ft_str_compare(&arg[2], "recursive") == 0)
			{
				FT_MEM_BIT_SET(_ls->options, RECURSIVE);
				continue;
			}

			if (ft_str_compare(&arg[2], "size") == 0)
			{
				FT_MEM_BIT_SET(_ls->options, SHOW_BLOCKS);
				continue;
			}

			if (ft_str_compare(&arg[2], "numeric-uid-gid") == 0)
			{
				FT_MEM_BIT_SET(_ls->options, FORMAT_LONG);
				FT_MEM_BIT_SET(_ls->options, OWNERS_NUM);
				continue;
			}

			show_error("unrecognized option", arg, false);
			ft_exit(FT_LS_EXIT_ERR_MINOR);
		}

		// Option (short)
		t_char const * cursor = arg;
		while (*++cursor != '\0')
		{
			switch (*cursor)
			{
				case 'a':
					FT_MEM_BIT_SET(_ls->options, SHOW_ALL);
					break;
				case 'c':
					FT_MEM_BIT_SET(_ls->options, USE_CTIME);
					FT_MEM_BIT_UNSET(_ls->options, USE_ATIME);
					break;
				case 'g':
					FT_MEM_BIT_SET(_ls->options, FORMAT_LONG);
					FT_MEM_BIT_SET(_ls->options, HIDE_USER);
					break;
				case 'G':
					FT_MEM_BIT_SET(_ls->options, HIDE_GROUP);
					break;
				case 'i':
					FT_MEM_BIT_SET(_ls->options, SHOW_INODE);
					break;
				case 'l':
					FT_MEM_BIT_SET(_ls->options, FORMAT_LONG);
					break;
				case 'n':
					FT_MEM_BIT_SET(_ls->options, FORMAT_LONG);
					FT_MEM_BIT_SET(_ls->options, OWNERS_NUM);
					break;
				case 'o':
					FT_MEM_BIT_SET(_ls->options, FORMAT_LONG);
					FT_MEM_BIT_SET(_ls->options, HIDE_GROUP);
					break;
				case 'p':
					FT_MEM_BIT_SET(_ls->options, DIR_SUFFIX);
					break;
				case 'r':
					FT_MEM_BIT_SET(_ls->options, SORT_REVERSE);
					break;
				case 'R':
					FT_MEM_BIT_SET(_ls->options, RECURSIVE);
					break;
				case 's':
					FT_MEM_BIT_SET(_ls->options, SHOW_BLOCKS);
					break;
				case 'S':
					FT_MEM_BIT_SET(_ls->options, SORT_SIZE);
					FT_MEM_BIT_UNSET(_ls->options, SORT_NONE);
					FT_MEM_BIT_UNSET(_ls->options, SORT_TIME);
					break;
				case 't':
					FT_MEM_BIT_SET(_ls->options, SORT_TIME);
					FT_MEM_BIT_UNSET(_ls->options, SORT_NONE);
					FT_MEM_BIT_UNSET(_ls->options, SORT_SIZE);
					break;
				case 'u':
					FT_MEM_BIT_SET(_ls->options, USE_ATIME);
					FT_MEM_BIT_UNSET(_ls->options, USE_CTIME);
					break;
				case 'U':
					FT_MEM_BIT_SET(_ls->options, SORT_NONE);
					FT_MEM_BIT_UNSET(_ls->options, SORT_SIZE);
					FT_MEM_BIT_UNSET(_ls->options, SORT_TIME);
				case '1':
					break;
				default:
				{
					t_char opt[2] = "-";
					opt[0] = *cursor;

					show_error("invalid option --", opt, false);
					ft_exit(FT_LS_EXIT_ERR_MINOR);
				}
			}
		}
	}

	if (!has_provided_file)
	{
		t_list * front = _load_file_info(_ls->files, ".");

		if (!front)
			ft_exit(FT_LS_EXIT_ERR_MINOR);

		_ls->files = front;
	}

	_ls->files = ft_lst_reverse(_ls->files); // Using push_front reverse dir order.
}
