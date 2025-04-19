/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:46:53 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/06 03:21:02 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <fcntl.h>
#include <stdlib.h>
#include "utils/utils.h"
#include "config.h"

static int	s_init_args(t_config *c, int ac, char *av[])
{
	int	t;

	if ((t = str_to_int(av[1])) <= 1)
		return (ret_error(1, "Error: config - invalid phi' number (> 1).\n"));
	c->number_of_philosopher = (size_t)t;
	if ((t = str_to_int(av[2])) < 0)
		return (ret_error(1, "Error: config - invalid time die (>= 0).\n"));
	c->time_to_die = (time_t)t;
	if ((t = str_to_int(av[3])) < 0)
		return (ret_error(1, "Error: config - invalid time eat (>= 0).\n"));
	c->time_to_eat = (time_t)t;
	if ((t = str_to_int(av[4])) < 0)
		return (ret_error(1, "Error: config - invalid time sleep (>= 0).\n"));
	c->time_to_sleep = (time_t)t;
	if (ac == 6 && (t = str_to_int(av[5])) < 0)
		return (ret_error(1, "Error: config - invalid meals number (>= 0).\n"));
	c->must_eat = (ac == 6) ? (size_t)t : 0;
	return (0);
}

static int	s_init_malloc(t_config *c)
{
	c->last_meal = malloc(sizeof(time_t) * c->number_of_philosopher);
	c->ate = malloc(sizeof(time_t) * c->number_of_philosopher);
	c->threads = malloc(sizeof(pid_t) * c->number_of_philosopher);
	c->death_monitors = malloc(sizeof(pthread_t) * c->number_of_philosopher);
	return (c->last_meal && c->ate && c->threads && c->death_monitors);
}

static int	s_init_semaphore(t_config *c)
{
	if ((c->can_eat = sem_open(SEM_N_CANEAT, O_CREAT,
		0644, c->number_of_philosopher / 2)) == SEM_FAILED)
		return (1);
	if ((c->chopsticks = sem_open(SEM_N_CHOPSTICKS, O_CREAT,
		0644, c->number_of_philosopher)) == SEM_FAILED)
		return (1);
	if ((c->write_locker = sem_open(SEM_N_WRITER, O_CREAT,
		0644, 1)) == SEM_FAILED)
		return (1);
	if ((c->death_locker = sem_open(SEM_N_DEATH, O_CREAT,
		0644, 1)) == SEM_FAILED)
		return (1);
	sem_unlink(SEM_N_CANEAT);
	sem_unlink(SEM_N_CHOPSTICKS);
	sem_unlink(SEM_N_WRITER);
	sem_unlink(SEM_N_DEATH);
	return (0);
}

static int	s_init_timer(t_config *c)
{
	size_t	i;

	c->started_at = get_time_ms(NULL);
	c->dead = 0;
	i = 0;
	while (i < c->number_of_philosopher)
	{
		c->last_meal[i] = c->started_at;
		c->ate[i] = 0;
		++i;
	}
	return (0);
}

int			config_init(t_config *c, int ac, char *av[])
{
	int	err;

	err = 0;
	if ((err = s_init_args(c, ac, av)))
		return (err);
	if (!(err = s_init_malloc(c)))
		return (ret_error(err, "Error: Config - Malloc failed.\n"));
	if ((err = s_init_semaphore(c)))
		return (ret_error(err, "Error: Config - Semaphore init failed.\n"));
	if ((err = s_init_timer(c)))
		return (ret_error(err, "Error: Config - Timer init failed.\n"));
	return (err);
}
