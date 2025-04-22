#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

// Typedef ---------------------------------------------------------------------
typedef struct s_cache t_cache;

// Struct ----------------------------------------------------------------------
struct s_cache
{
	t_fd fd;
	t_size index;
	t_char buffer[FT_IO_GNL_BUFFER_SIZE];
};

// Declaration -----------------------------------------------------------------
static t_ssize _read_line(t_cache * _gnl, t_char ** _line);

static t_list * _cache_create(t_list * _lst, t_fd _fd);
static t_list * _cache_get(t_list const * _lst, t_fd _fd);
static t_list * _cache_delete(t_list * _node);

// Function --------------------------------------------------------------------
t_ssize
ft_get_next_line(
	t_fd _fd,
	t_char ** _line
)
{
	if (!_line || _fd < 0)
		return (-1);

	static t_list * caches;

	t_list * node = _cache_get(caches, _fd);
	if (!node)
	{
		node = _cache_create(caches, _fd);

		if (!node)
			return (-1);

		caches = node;
	}

	t_ssize read_len = _read_line(node->data, _line);
	if (read_len <= 0)
	{
		caches = _cache_delete(node);

		if (read_len == -1)
			*_line = nullptr;
	}

	return (read_len);
}

// Static ----------------------------------------------------------------------
static t_ssize
_read_line(
	t_cache * _cache,
	t_char ** _line
)
{
	t_char * old_line;
	t_char * separator;
	t_ssize read_len;

	while (true)
	{
		if (_cache->index != 0)
			read_len = FT_IO_GNL_BUFFER_SIZE - 1;
		else if ((read_len = read(_cache->fd, _cache->buffer, FT_IO_GNL_BUFFER_SIZE - 1)) < 0)
			return (-1);

		_cache->buffer[read_len] = '\0';

		if ((separator = ft_str_find_chr(&_cache->buffer[_cache->index], '\n')))
			*separator = '\0';

		old_line = *_line;
		*_line = ft_str_join(*_line, &_cache->buffer[_cache->index]);

		if (old_line)
			free(old_line);
		if (!*_line)
			return (-1);

		if (separator)
		{
			_cache->index = (separator - _cache->buffer + 1);
			return (1);
		}

		_cache->index = 0;
	}

	return (read_len);
}

static t_list *
_cache_create(
	t_list * _lst,
	t_fd _fd
)
{
	t_cache * cache = malloc(sizeof(t_cache));

	if (!cache)
		return (nullptr);

	cache->fd = _fd;
	cache->index = 0;
	cache->buffer[0] = '\0';
	cache->buffer[FT_IO_GNL_BUFFER_SIZE - 1] = '\0';

	t_list * node = ft_lst_push_front(_lst, cache);

	if (!node)
	{
		free(cache);
		return (nullptr);
	}

	return (node);
}

static t_list *
_cache_get(
	t_list const * _lst,
	t_fd _fd
)
{
	while (_lst)
	{
		if (((t_cache const *)_lst->data)->fd == _fd)
			return ((t_list *)_lst);

		_lst = _lst->next;
	}

	return (nullptr);
}

static t_list *
_cache_delete(
	t_list * _node
)
{
	t_list * front = ft_lst_front(_node);
	t_list * next = ft_lst_delete(_node, free);

	if (front == _node)
		return (next);

	return (front);
}
