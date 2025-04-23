#ifndef LIBFT_CHAR_H
#define LIBFT_CHAR_H

#include "ft_types.h"

// Function --------------------------------------------------------------------
t_bool ft_chr_is_alnum(t_char _chr);
t_bool ft_chr_is_alpha(t_char _chr);
t_bool ft_chr_is_ascii(t_char _chr);
t_bool ft_chr_is_blank(t_char _chr);
t_bool ft_chr_is_digit(t_char _chr);
t_bool ft_chr_is_print(t_char _chr);
t_bool ft_chr_is_space(t_char _chr);

t_char ft_chr_to_lower(t_char _chr);
t_char ft_chr_to_upper(t_char _chr);

#endif
