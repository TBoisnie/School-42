/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 07:53:05 by tboisnie          #+#    #+#             */
/*   Updated: 2019/12/04 15:03:50 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <stddef.h>

typedef struct	s_placeholder
{
	char				flags;
	int					width;
	int					precision;
	char				length;
	char				type;

	char				has_dot;

	char				*str;
	long long			value;
	unsigned long long	uvalue;
	short				offset;

	int					error;
}				t_placeholder;

void			add_flag(const char flag, t_placeholder *ph);
void			remove_flag(const char flag, t_placeholder *ph);
int				has_flag(const char flag, t_placeholder *ph);

char			*ft_ulltoa_base(unsigned long long n, char *base);
char			*ft_lltoa_base(long long n, char *base);
char			*int_to_struchar(int n);
char			*ptr_to_strhex(uintptr_t ptr);

void			apply_flags(t_placeholder *ph);
void			apply_width(t_placeholder *ph, size_t len, int append,
					int *count);
void			apply_precision(t_placeholder *ph);
void			apply_type(t_placeholder *ph, va_list *args);

const char		*check_flags(const char *fmt, t_placeholder *ph);
const char		*check_width(const char *fmt, t_placeholder *ph,
					va_list *args);
const char		*check_precision(const char *fmt, t_placeholder *ph,
					va_list *args);
const char		*check_length(const char *fmt, t_placeholder *ph);
const char		*check_type(const char *fmt, t_placeholder *ph);

const char		*parse(const char *fmt, va_list *args, int *count);

int				ft_printf(const char *fmt, ...);

#endif
