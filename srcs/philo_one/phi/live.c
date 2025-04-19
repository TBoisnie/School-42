/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:30:35 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/05 16:26:03 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "monitor/monitor.h"
#include "utils/utils.h"
#include "phi.h"

static int	s_live_routine(t_config *c, size_t pos, size_t left, size_t right)
{
	phi_set_status(c, pos, THINK, 1);
	if (pthread_mutex_lock(&c->chopsticks[left]))
		return (ret_error(1, "Error: phi_live - Mutex lock failed.\n"));
	phi_set_status(c, pos, PICK, 1);
	if (pthread_mutex_lock(&c->chopsticks[right]))
	{
		pthread_mutex_unlock(&c->chopsticks[left]);
		return (ret_error(1, "Error: phi_live - Mutex lock failed.\n"));
	}
	phi_set_status(c, pos, PICK, 1);
	phi_set_status(c, pos, EAT, 1);
	++c->ate[pos];
	sleep_ms(c->time_to_eat);
	if (pthread_mutex_unlock(&c->chopsticks[right]))
		return (ret_error(1, "Error: phi_live - Mutex unlock failed.\n"));
	if (pthread_mutex_unlock(&c->chopsticks[left]))
		return (ret_error(1, "Error: phi_live - Mutex unlock failed.\n"));
	phi_set_status(c, pos, SLEEP, 1);
	sleep_ms(c->time_to_sleep);
	return (0);
}

static void	*s_live(void *args_v)
{
	t_args	*args;
	size_t	left;
	size_t	right;

	args = args_v;
	if (monitor_death_start(args))
		return (0);
	args->c->last_meal[args->pos] = get_time_ms(NULL);
	left = min(args->pos, (args->pos + 1) % args->c->number_of_philosopher);
	right = max(args->pos, (args->pos + 1) % args->c->number_of_philosopher);
	while (!args->c->dead && (!args->c->must_eat
		|| args->c->ate[args->pos] < args->c->must_eat))
	{
		if (s_live_routine(args->c, args->pos, left, right))
			break ;
	}
	if (pthread_join(args->c->death_monitors[args->pos], NULL))
		ret_error(1, "Error: death_m - pthread join failed.\n");
	return (0);
}

int			phi_live_start(t_config *c, t_args *args)
{
	size_t	i;

	i = 0;
	while (i < c->number_of_philosopher)
	{
		if (pthread_create(&c->threads[i], NULL, s_live, &args[i]))
			return (ret_error(1, "Error: phi_live - pthread create failed.\n"));
		usleep(25);
		i += 2;
	}
	i = 1;
	while (i < c->number_of_philosopher)
	{
		if (pthread_create(&c->threads[i], NULL, s_live, &args[i]))
			return (ret_error(1, "Error: phi_live - pthread create failed.\n"));
		usleep(25);
		i += 2;
	}
	return (0);
}

int			phi_live_wait(t_config *c)
{
	size_t	i;

	i = 0;
	while (i < c->number_of_philosopher)
	{
		if (pthread_join(c->threads[i], NULL))
			return (ret_error(1, "Error: phi_live - pthread join failed.\n"));
		++i;
	}
	return (0);
}
