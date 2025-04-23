#include <pthread.h>
#include "libft/incs/ft_memory.h"
#include "zone.h"
#include "malloc.h"

// Global ----------------------------------------------------------------------
extern t_zones g_malloc_zones;
extern pthread_mutex_t g_malloc_mutex;

// Function --------------------------------------------------------------------
void * realloc(void * ptr, size_t size)
{
	if (!ptr)
	{
		return malloc(size);
	}

	pthread_mutex_lock(&g_malloc_mutex);

	t_chunk * chunk = ptr;
	--chunk;

	if (CHUNK_IS_FREE(chunk))
	{
		// Todo: Trigger error (invalid pointer)
		return (nullptr);
	}

	// Shrink
	size = CHUNK_ALIGN_SIZE(size);

	if (size <= CHUNK_GET_SIZE(chunk))
	{
		_chunk_allocate(chunk, size);
		_chunk_deallocate(_chunk_get_next(chunk)); // To merge free chunk
		return (chunk);
	}

	// Expand
	t_chunk * next = _chunk_get_next(chunk);

	if (next && CHUNK_IS_FREE(next))
	{
		t_size available_size =
			CHUNK_GET_SIZE(chunk) + CHUNK_GET_SIZE(next) + 2 * sizeof(t_chunk);

		if (size <= available_size)
		{
			_chunk_merge(chunk, next);
			_chunk_allocate(chunk, size);
			return (chunk);
		}
	}

	pthread_mutex_unlock(&g_malloc_mutex);

	// Move
	ptr = malloc(size);

	pthread_mutex_lock(&g_malloc_mutex);

	if (!ptr)
	{
		// Todo: Trigger error (No more space)
		return (nullptr);
	}

	t_byte * b = (t_byte *)chunk;
	b += sizeof(t_chunk);

	ft_mem_copy((t_chunk*)b, ptr, CHUNK_GET_SIZE(chunk));

	pthread_mutex_unlock(&g_malloc_mutex);

	free(b);

	return (ptr);
}
