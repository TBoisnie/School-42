#ifndef FT_LS_H
#define FT_LS_H

#include <sys/stat.h>
#include "libft/incs/container/ft_list.h"
#include "libft/incs/ft_types.h"
#include "libft/incs/ft_limits.h"

// =============================================================================
// Public
// =============================================================================
// Define ----------------------------------------------------------------------
#define FT_LS_EXIT_ERR_MINOR (1)
#define FT_LS_EXIT_ERR_MAJOR (2)

#define FT_LS_DATE_LIMIT_IN_SECONDS (15780000) // 6 Months ago

#define USAGE \
	"List information about the files (current directory by default)\n" \
	"\nUsage: ft_ls [options...] [file...]\n\n" \
	"Options:\n" \
		"    -a, --all               Do not ignore entries starting with '.'.\n" \
		"    -c                      With '-lt': sort by, and show, ctime. With '-l': show ctime and sort by name. Otherwise: sort by ctime, newest first.\n" \
		"    --color                 Enable colored output.\n" \
		"    -g                      Like '-l', but hide owner user.\n" \
		"    -G, --no-group          With '-l', don't print group names.\n" \
		"    --help                  Display this help and exit.\n" \
		"    -i, --inode             Print the index number of each file.\n" \
		"    -l                      Use a long listing format.\n" \
		"    -n, --numeric-uid-gid   Like '-l', but list numeric user and group IDs.\n" \
		"    -o                      Like '-l', but do not list group information.\n" \
		"    -p                      Append '/' indicator to directories.\n" \
		"    -r, --reverse           Reverse order while sorting.\n" \
		"    -R, --recursive         List subdirectories recursively.\n" \
		"    -s, --size              Print the allocated size of each file, in blocks.\n" \
		"    -S                      Sort by file size, largest first.\n" \
		"    -t                      Sort by time, newest first.\n" \
		"    -u                      With '-lt': sort by, and show, access time. With '-l': show access time and sort by name. Otherwise: sort by access time, newest first.\n" \
		"    -U                      Do not sort. List entries in directory order.\n" \
		"    --zero                  End each output line with NUL ('\\0'), instead of newline ('\\n').\n" \
		"    -1                      List one file per line (always active).\n"

// Enum ------------------------------------------------------------------------
typedef enum
{
	SHOW_ALL     = 1 << 0,
	FORMAT_LONG  = 1 << 1,
	RECURSIVE    = 1 << 2,
	SORT_REVERSE = 1 << 3,
	SORT_TIME    = 1 << 4,
	SORT_SIZE    = 1 << 5,
	COLOR        = 1 << 6,
	SHOW_INODE   = 1 << 7,
	HIDE_GROUP   = 1 << 8,
	HIDE_USER    = 1 << 9,
	SHOW_BLOCKS  = 1 << 10,
	ZERO_END     = 1 << 11,
	OWNERS_NUM   = 1 << 12,
	USE_ATIME    = 1 << 13,
	USE_CTIME    = 1 << 14,
	DIR_SUFFIX   = 1 << 15,
	SORT_NONE    = 1 << 16
} t_ls_option;

// Struct ----------------------------------------------------------------------
typedef struct
{
	t_char * name;
	t_char fullpath[FT_PATH_MAX];
	t_char target[FT_PATH_MAX];
	struct stat stats;
	t_char user_name[256];
	t_uint user_id;
	t_char group_name[256];
	t_uint group_id;
} t_file;

typedef struct
{
	t_uint inode;
	t_uint blocks;
	t_uint links;
	t_uint group;
	t_uint user;
	t_uint size;
	t_uint major;
	t_uint minor;
	t_uint date;
	t_uint time;
} t_columns;

typedef struct
{
	t_uint options;
	t_list * files;
	t_columns columns;
	t_int exit_code;
} t_ls;

// Function --------------------------------------------------------------------
t_void parse_args(t_int _argc, t_char * _argv[], t_ls * _ls);

t_file * file_new(t_char const * _fullpath);
t_file * file_init(t_file * _file);

t_void render_folder(t_list * _lst, t_ls * _ls);
t_void render_file(t_file const * _file, t_ls const * _ls, t_bool _force_show);
t_void render_set_columns_sizes(t_file const * _file, t_ls * _ls);

t_ssize compare_by_atime(t_void const * _file_1, t_void const * _file_2);
t_ssize compare_by_ctime(t_void const * _file_1, t_void const * _file_2);
t_ssize compare_by_mtime(t_void const * _file_1, t_void const * _file_2);
t_ssize compare_by_name(t_void const * _file_1, t_void const * _file_2);
t_ssize compare_by_size(t_void const * _file_1, t_void const * _file_2);
t_ssize compare_by_type(t_void const * _file_1, t_void const * _file_2);
t_list_func_cmp get_compare_func(t_ls const * _ls);

t_void show_error(t_char const * _message, t_char const * _detail, t_bool _show_errno);

#endif
