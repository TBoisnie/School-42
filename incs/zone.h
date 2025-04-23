#ifndef LIBFT_MALLOC_ZONE_H
#define LIBFT_MALLOC_ZONE_H

#include "libft/incs/ft_limits.h"
#include "libft/incs/ft_types.h"
#include "block.h"

// Enum ------------------------------------------------------------------------
#define ZONE_GET_CHUNK_MAX_SIZE(zone) ((t_size)zone)

// Enum ------------------------------------------------------------------------
typedef enum
{
	SMALL  = 1024,
	MEDIUM = 4096,
	LARGE  = FT_SIZE_MAX,
} t_zone_type;

// Struct ----------------------------------------------------------------------
typedef struct
{
	t_block * small;
	t_block * medium;
	t_block * large;
} t_zones;

// Function --------------------------------------------------------------------
t_zone_type _zone_determine_type(t_size size);
t_chunk *   _zone_find_free_chunk(t_block * block, t_size size);

#endif
