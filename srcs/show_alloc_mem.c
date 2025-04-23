#include <pthread.h>
#include "zone.h"
#include "malloc.h"
#include "libft/incs/ft_number.h"
#include "libft/incs/ft_io.h"

// Global ----------------------------------------------------------------------
extern t_zones g_malloc_zones;
extern pthread_mutex_t g_malloc_mutex;

// Function --------------------------------------------------------------------
static void
show_chunk(t_chunk * chunk, t_size * total)
{
	t_byte * data = (t_byte *)chunk;
	data += sizeof(t_chunk);

	ft_printf(
		"%p - %p : %lu bytes\n",
		data, data + CHUNK_GET_SIZE(chunk), CHUNK_GET_SIZE(chunk)
	);

	*total += CHUNK_GET_SIZE(chunk);
}

static void
show_block(t_char * type, t_block * block, t_size * total)
{
	t_chunk * chunk;

	ft_printf("%s : %p\n", type, &block->chunks);

	chunk = &block->chunks;
	while(chunk)
	{
		if (!CHUNK_IS_FREE(chunk))
		{
			show_chunk(chunk, total);
		}
		chunk = _chunk_get_next(chunk);
	}
}

static void
show_zone(t_char * type, t_block * zone, t_size * total)
{
	t_block * block;

	block = zone;
	while (block)
	{
		show_block(type, block, total);
		block = block->next;
	}
}

void
show_alloc_mem()
{
	t_size total = 0;

	pthread_mutex_lock(&g_malloc_mutex);

	show_zone("TINY",  g_malloc_zones.small,  &total);
	show_zone("SMALL", g_malloc_zones.medium, &total);
	show_zone("LARGE", g_malloc_zones.large,  &total);

	pthread_mutex_unlock(&g_malloc_mutex);

	ft_printf("Total : %lu bytes\n", total);
}
