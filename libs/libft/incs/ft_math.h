#ifndef LIBFT_MATH_H
#define LIBFT_MATH_H

#include "ft_types.h"

// Macro -----------------------------------------------------------------------
#define FT_MATH_ABS(_x) \
	((_x) * (((_x) > 0) - ((_x) < 0)))
#define FT_MATH_MIN(_x, _y) \
	(((_x) < (_y)) ? (_x) : (_y))
#define FT_MATH_MAX(_x, _y) \
	(((_x) > (_y)) ? (_x) : (_y))
#define FT_MATH_CLAMP(_x, _min, _max) \
	(((_x) < (_min)) ? (_min) : ((_x) > (_max)) ? (_max) : (_x))
// Round x to the next p multiple (p must be a power of 2)
#define FT_MATH_ROUND_POWER_2(_x, _p) \
	(((_x) + ((_p) - 1)) & ~((_p) - 1))

// Function --------------------------------------------------------------------

#endif
