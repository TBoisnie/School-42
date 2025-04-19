/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:51:36 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/10 17:30:48 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <stddef.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# define SEM_N_CHOPSTICKS	"phi_two_chopsticks_sem"
# define SEM_N_WRITER		"phi_two_writer_sem"
# define SEM_N_CANEAT		"phi_two_caneat_sem"

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

	sem_t			*chopsticks;
	sem_t			*can_eat;
	sem_t			*write_locker;

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
