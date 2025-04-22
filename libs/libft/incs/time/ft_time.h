#ifndef LIBFT_TIME_H
#define LIBFT_TIME_H

#include "../core/ft_types.h"

// Typedef ---------------------------------------------------------------------
typedef struct s_time t_time;
typedef struct s_date t_date;

// Struct ----------------------------------------------------------------------
struct s_time
{
	t_uint_8 hour;
	t_uint_8 minute;
	t_uint_8 second;
	t_uint_16 milli_second;
	t_uint_16 micro_second;
};

struct s_date
{
	t_uint_16 year;
	t_uint_8 month;
	t_uint_8 day;
};

// Function --------------------------------------------------------------------

#endif
