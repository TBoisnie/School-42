#include "zone.h"

t_zone_type
_zone_determine_type(t_size size)
{
	if (size <= ZONE_GET_CHUNK_MAX_SIZE(SMALL))
		return (SMALL);
	if (size <= ZONE_GET_CHUNK_MAX_SIZE(MEDIUM))
		return (MEDIUM);
	return (LARGE);
}
