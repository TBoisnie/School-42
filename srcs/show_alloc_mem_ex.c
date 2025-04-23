#include <pthread.h>
#include "zone.h"
#include "malloc.h"
#include "libft/incs/ft_char.h"
#include "libft/incs/ft_io.h"

// Global ----------------------------------------------------------------------
extern t_zones g_malloc_zones;
extern pthread_mutex_t g_malloc_mutex;

// Function --------------------------------------------------------------------
static t_char
byte_to_chr(
	t_byte _byte
)
{
	if (ft_chr_is_print(_byte))
		return (_byte);
	return ('.');
}

static void
show_chunk(t_chunk * chunk)
{
	t_byte * data = (t_byte *)chunk;
	data += sizeof(t_chunk);

	t_size size = CHUNK_GET_SIZE(chunk);

	while (size)
	{
		ft_printf(
			"%12p | %.8b %.8b %.8b %.8b %.8b %.8b %.8b %.8b | %c%c%c%c%c%c%c%c\n",
			data+8,
			*(data+0), *(data+1), *(data+2), *(data+3),
			*(data+4), *(data+5), *(data+6), *(data+7),
			byte_to_chr(*(data+0)), byte_to_chr(*(data+1)), byte_to_chr(*(data+2)),
			byte_to_chr(*(data+3)), byte_to_chr(*(data+4)), byte_to_chr(*(data+5)),
			byte_to_chr(*(data+6)), byte_to_chr(*(data+7))
		);
		size -= CHUNK_ALIGN_MASK;
		data += CHUNK_ALIGN_MASK;
	}
}

static void
show_block(t_block * block)
{
	t_chunk * chunk;

	chunk = &block->chunks;
	while(chunk)
	{
		if (!CHUNK_IS_FREE(chunk))
		{
			show_chunk(chunk);

			t_char * ph = "................";
			ft_printf(
				"%.14s | %.8s %.8s %.8s %.8s %.8s %.8s %.8s %.8s | %.8s\n",
				ph, ph, ph, ph, ph, ph, ph, ph, ph, ph
			);
		}
		chunk = _chunk_get_next(chunk);
	}
}

static void
show_zone(t_block * zone)
{
	t_block * block;

	block = zone;
	while (block)
	{
		show_block(block);
		block = block->next;
	}
}

void
show_alloc_mem_ex()
{
	pthread_mutex_lock(&g_malloc_mutex);

	show_zone(g_malloc_zones.small);
	show_zone(g_malloc_zones.medium);
	show_zone(g_malloc_zones.large);

	pthread_mutex_unlock(&g_malloc_mutex);
}
