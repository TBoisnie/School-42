#include "libft.h"

// Function --------------------------------------------------------------------
t_double
ft_math_sqrt(
	t_double _x,
	t_double _precision
)
{
	if (_x < _precision)
	{
		return (0.0);
	}

	t_double a;
	t_double b = _x / 2;

	do
	{
		a = b;
		b = (a + _x / a) / 2;
	}
	while (FT_MATH_ABS(b - a) > _precision);

	return (b);
}
