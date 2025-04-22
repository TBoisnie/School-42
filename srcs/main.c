#include <stdlib.h>
#include "libft/incs/ft_io.h"
#include "libft/incs/ft_memory.h"
#include "libft/incs/ft_string.h"
#include "libft/incs/ft_system.h"
#include "ft_ls.h"

static t_bool
_is_folder(
	t_void const * _data,
	t_size _index
)
{
	(void)_index;
	return (S_ISDIR(((t_file *)_data)->stats.st_mode));
}

int
main(
	int _argc,
	char * _argv[]
)
{
	t_ls ls =
	{
		.options = 0,
		.files = nullptr,
		.columns =
		{
			.inode = 0,
			.blocks = 0,
			.links = 0,
			.group = 0,
			.user = 0,
			.size = 0,
			.major = 0,
			.minor = 0,
			.date = 0,
			.time = 0
		},
		.exit_code = FT_EXIT_OK
	};

	parse_args(_argc, _argv, &ls);

	// Sort
	ls.files = ft_lst_sort(ls.files, compare_by_type, false);

	t_list * node = nullptr;
	if (!FT_MEM_BIT_ISSET(ls.options, SORT_NONE))
	{
		t_list_func_cmp cmp = get_compare_func(&ls);
		t_bool reverse = FT_MEM_BIT_ISSET(ls.options, SORT_REVERSE);

		node = ft_lst_find(ls.files, _is_folder);

		if (node)
		{
			ls.files = ft_lst_sort_range(ls.files, node->prev, cmp, reverse);
			ls.files = ft_lst_sort_range(node, nullptr, cmp, reverse);
		}
		else
		{
			ls.files = ft_lst_sort(ls.files, cmp, reverse);
		}
	}

	// Columns
	if (FT_MEM_BIT_ISSET(ls.options, FORMAT_LONG))
	{
		t_list * tmp = nullptr;

		if (node && node->prev)
		{
			tmp = node->prev->next;
			node->prev->next = nullptr;
		}

		t_list const * current;
		for (current = ls.files; current != nullptr; current = current->next)
		{
			render_set_columns_sizes(current->data, &ls);
		}

		if (tmp)
			node->prev->next = tmp;
	}

	// Render
	node = ls.files;
	while (node)
	{
		t_file * file = node->data;

		if (!FT_MEM_BIT_ISSET(ls.options, FORMAT_LONG) && S_ISLNK(file->stats.st_mode))
		{
			t_char target[FT_PATH_MAX] = "";

			if (file->target[0] != '/')
			{
				t_char * path = ft_str_rfind_chr(file->fullpath, '/');
				if (path)
					ft_str_copy_limit(file->fullpath, target, path - file->fullpath + 1);
			}

			ft_str_concat(target, file->target);

			struct stat stat_target;
			if (stat(target, &stat_target) == 0)
			{
				if (S_ISDIR(stat_target.st_mode))
					render_folder(node, &ls);
				else
					render_file(file, &ls, true);
			}
			else
			{
				render_file(file, &ls, true);
			}
		}
		else if (S_ISDIR(file->stats.st_mode))
		{
			render_folder(node, &ls);
		}
		else
		{
			render_file(file, &ls, true);
		}

		node = node->next;
	}

	ft_lst_clear(ls.files, free);

	return (ls.exit_code);
}
