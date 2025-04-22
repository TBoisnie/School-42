#ifndef LIBFT_MATH_H
#define LIBFT_MATH_H

#include "../core/ft_types.h"

// Macro -----------------------------------------------------------------------
#define FT_MATH_ABS(x) \
	((x) * (((x) > 0) - ((x) < 0)))
#define FT_MATH_MIN(x, y) \
	(((x) < (y)) ? (x) : (y))
#define FT_MATH_MAX(x, y) \
	(((x) > (y)) ? (x) : (y))
#define FT_MATH_CLAMP(x, min, max) \
	(FT_MATH_MIN(FT_MATH_MAX(x, min), max))
// Round x to the next p multiple (p must be a power of 2)
#define FT_MATH_ROUND_POWER_2(x, p) \
	(((x) + ((p) - 1)) & ~((p) - 1))

// Function --------------------------------------------------------------------
t_double ft_math_sqrt(t_double _x, t_double _precision);

#endif
