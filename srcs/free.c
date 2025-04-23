#include <pthread.h>
#include "zone.h"
#include "malloc.h"

// Global ----------------------------------------------------------------------
extern t_zones g_malloc_zones;
extern pthread_mutex_t g_malloc_mutex;

// Function --------------------------------------------------------------------
void free(void * ptr)
{
	if (!ptr)
	{
		return;
	}

	pthread_mutex_lock(&g_malloc_mutex);

	t_chunk * chunk = ptr;
	--chunk;

	if (CHUNK_IS_FREE(chunk))
	{
		// Todo: Trigger error (double free)
		return;
	}

	t_zone_type zone_type = _zone_determine_type(CHUNK_GET_SIZE(chunk));

	chunk = _chunk_deallocate(chunk);

	if (BLOCK_IS_EMPTY(chunk))
	{
		t_byte * b = (t_byte *)chunk;
		b -= sizeof(t_block) - sizeof(t_chunk);

		t_block * block = (t_block *)b;
		if (zone_type == LARGE || block->prev || block->next)
		{
			block = _block_delete(block);

			switch (zone_type)
			{
				case SMALL:
					g_malloc_zones.small = block;
					break;
				case MEDIUM:
					g_malloc_zones.medium = block;
					break;
				case LARGE:
					g_malloc_zones.large = block;
					break;
			}
		}
	}

	pthread_mutex_unlock(&g_malloc_mutex);
}
