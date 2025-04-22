#ifndef LIBFT_IO_GNL_H
#define LIBFT_IO_GNL_H

#include "../core/ft_types.h"

// Define ----------------------------------------------------------------------
#ifdef FT_IO_GNL_BUFFER_SIZE
	#if FT_IO_GNL_BUFFER_SIZE <= 1
		#warning __FILE__":"__LINE__": Invalid FT_IO_GNL_BUFFER_SIZE (must be > 1), will use default value."
		#undef FT_IO_GNL_BUFFER_SIZE
	#endif
#endif

#ifndef FT_IO_GNL_BUFFER_SIZE
	#define FT_IO_GNL_BUFFER_SIZE  4096
#endif

// Function --------------------------------------------------------------------
/**
 * Read a file descriptor until a new-line or end-of-file is found,
 * and set the `_line` to the newly allocated one.
 * Each call on the same file descriptor increment cursor location to the next line.
 *
 * @param _fd: File descriptor to read from
 * @param _line: Pointer to the newly allocated string
 *
 * @return `1` if a line is read, `0` otherwise
 *
 * @exception If allocation or read failed, `-1` is returned
 *
 * @warning Each file descriptor has its own (allocated) cache until end-of-file
 * is reached
**/
t_ssize ft_get_next_line(t_fd _fd, t_char ** _line);


#endif
