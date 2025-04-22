#include <dirent.h>
#include <stdlib.h>
#include "libft/incs/ft_io.h"
#include "libft/incs/ft_limits.h"
#include "libft/incs/ft_memory.h"
#include "libft/incs/ft_string.h"
#include "libft/incs/ft_system.h"
#include "ft_ls.h"

t_void
render_folder(
	t_list * _root,
	t_ls * _ls
)
{
	t_list * node;
	t_file * file = _root->data;

	// Read
	DIR * dir = opendir(file->fullpath);

	if (!dir)
	{
		show_error("cannot open directory", file->fullpath, true);
		_ls->exit_code = FT_LS_EXIT_ERR_MINOR;
		return;
	}

	// Format path
	t_char dir_path[FT_PATH_MAX];
	ft_str_copy(file->fullpath, dir_path);
	t_char * dir_path_end = dir_path + ft_str_length(dir_path);

	if (*(dir_path_end - 1) != '/')
	{
		*dir_path_end++ = '/';
		*dir_path_end   = '\0';
	}

	// Content
	t_list * entries = nullptr;

	struct dirent * entry;
	while ((entry = readdir(dir)))
	{
		ft_str_copy(entry->d_name, dir_path_end);

		file = file_new(dir_path);

		if (!file)
			ft_exit(FT_LS_EXIT_ERR_MINOR);

		node = ft_lst_push_front(entries, file);

		if (!node)
		{
			show_error("cannot allocate memory (render_folder:ft_lst_push_front)", nullptr, true);
			ft_exit(FT_LS_EXIT_ERR_MAJOR);
		}

		entries = node;
	}

	closedir(dir);

	// Sort
	entries = ft_lst_reverse(entries); // Using push_front reverse dir order

	if (!FT_MEM_BIT_ISSET(_ls->options, SORT_NONE))
	{
		entries = ft_lst_sort(entries, get_compare_func(_ls), FT_MEM_BIT_ISSET(_ls->options, SORT_REVERSE));
	}


	if (_root != _ls->files)
		ft_printf("\n");

	// Location
	if (FT_MEM_BIT_ISSET(_ls->options, RECURSIVE) || _root->prev || _root->next)
	{
		ft_printf("%s:\n", ((t_file *)_root->data)->fullpath);
	}

	// Total
	t_size block_total = 0;

	_ls->columns.inode = 0;
	_ls->columns.blocks = 0;
	_ls->columns.links = 0;
	_ls->columns.group = 0;
	_ls->columns.user = 0;
	_ls->columns.size = 0;
	_ls->columns.major = 0;
	_ls->columns.minor = 0;
	_ls->columns.date = 0;
	_ls->columns.time = 0;

	node = entries;
	while (node)
	{
		file = node->data;

		if (FT_MEM_BIT_ISSET(_ls->options, SHOW_ALL) || !(file->name[0] == '.'))
		{
			block_total += file->stats.st_blocks;
			render_set_columns_sizes(file, _ls);
		}

		node = node->next;
	}

	if (
		FT_MEM_BIT_ISSET(_ls->options, FORMAT_LONG) ||
		FT_MEM_BIT_ISSET(_ls->options, SHOW_BLOCKS)
	)
	{
		ft_printf("total %lu%c",
			(block_total + 1) / 2,
			FT_MEM_BIT_ISSET(_ls->options, ZERO_END) ? '\0' : '\n'
		);
	}

	// Render
	node = entries;
	while (node)
	{
		render_file(node->data, _ls, false);
		node = node->next;
	}

	// Recursion
	if (FT_MEM_BIT_ISSET(_ls->options, RECURSIVE))
	{
		node = entries;
		while (node)
		{
			file = node->data;

			if (!S_ISDIR(file->stats.st_mode))
			{
				node = node->next;
				continue;
			}

			if (
				!ft_str_compare(file->name, ".") ||
				!ft_str_compare(file->name, "..")
			)
			{
				node = node->next;
				continue;
			}

			if (FT_MEM_BIT_ISSET(_ls->options, SHOW_ALL) || !(file->name[0] == '.'))
			{
				render_folder(node, _ls);
			}

			node = node->next;
		}
	}

	ft_lst_clear(entries, free);
}
