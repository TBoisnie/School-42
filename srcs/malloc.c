#include <pthread.h>
#include "zone.h"
#include "malloc.h"

// Global ----------------------------------------------------------------------
t_zones g_malloc_zones =
{
	.small = nullptr,
	.medium = nullptr,
	.large = nullptr
};

pthread_mutex_t g_malloc_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function --------------------------------------------------------------------
void * malloc(size_t size)
{
	if (size == 0)
	{
		return (nullptr);
	}

	size = CHUNK_ALIGN_SIZE(size);

	t_zone_type zone_type = _zone_determine_type(size);

	pthread_mutex_lock(&g_malloc_mutex);

	t_block * zone;
	switch (zone_type)
	{
		case SMALL:
			zone = g_malloc_zones.small;
			break;
		case MEDIUM:
			zone = g_malloc_zones.medium;
			break;
		case LARGE:
			zone = g_malloc_zones.large;
			break;
	}

	t_chunk * chunk = _zone_find_free_chunk(zone, size);

	if (!chunk)
	{
		t_size block_size;
		if (zone_type == LARGE)
			block_size = _block_align_size(size, 1);
		else
		{
			block_size = _block_align_size(
				ZONE_GET_CHUNK_MAX_SIZE(zone_type),
				BLOCK_ALLOC_MIN
			);
		}

		t_block * block = _block_create(zone, block_size);

		if (!block)
		{
			// Todo: Trigger error (mmap failed)
			return (nullptr);
		}

		if (!zone)
		{
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

		chunk = &block->chunks;
	}

	chunk = _chunk_allocate(chunk, size);

	pthread_mutex_unlock(&g_malloc_mutex);

	return (++chunk);
}
