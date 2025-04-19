/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:51:36 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/09 01:26:10 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <stddef.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum	e_phi_status
{
	THINK,
	PICK,
	EAT,
	SLEEP,
	DIE
}				t_phi_status;

typedef struct	s_config
{
	size_t			number_of_philosopher;
	size_t			must_eat;

	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			started_at;

	time_t			*last_meal;
	size_t			*ate;
	size_t			dead;

	pthread_mutex_t	*chopsticks;
	pthread_mutex_t	write_locker;

	pthread_t		*threads;
	pthread_t		*death_monitors;
}				t_config;

typedef struct	s_args
{
	t_config	*c;
	size_t		pos;
}				t_args;

int				config_init(t_config *c, int ac, char *av[]);
void			config_clear(t_config *c);

#endif
