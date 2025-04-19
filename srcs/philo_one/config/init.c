/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:46:53 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/09 18:44:36 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
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
	c->chopsticks = malloc(sizeof(pthread_mutex_t) * c->number_of_philosopher);
	c->threads = malloc(sizeof(pthread_t) * c->number_of_philosopher);
	c->death_monitors = malloc(sizeof(pthread_t) * c->number_of_philosopher);
	return (c->last_meal && c->ate && c->chopsticks && c->threads &&
		c->death_monitors);
}

static int	s_init_mutex(t_config *c)
{
	size_t	i;
	int		failed;

	failed = 0;
	i = 0;
	while (i < c->number_of_philosopher && !failed)
	{
		if (pthread_mutex_init(&c->chopsticks[i], NULL))
			++failed;
		++i;
	}
	if (pthread_mutex_init(&c->write_locker, NULL))
		++failed;
	return (failed);
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
		return (ret_error(err, "Error: config - Malloc failed."));
	if ((err = s_init_mutex(c)))
		return (ret_error(err, "Error: config - Mutex init failed."));
	if ((err = s_init_timer(c)))
		return (ret_error(err, "Error: config - Timer init failed."));
	return (err);
}
