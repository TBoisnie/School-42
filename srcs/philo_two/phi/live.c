/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 18:30:35 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/05 16:26:21 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "monitor/monitor.h"
#include "utils/utils.h"
#include "phi.h"

static int	s_live_routine(t_config *c, size_t pos)
{
	phi_set_status(c, pos, THINK, 1);
	if (sem_wait(c->can_eat))
		return (ret_error(1, "Error: phi_live - Sem wait failed.\n"));
	if (sem_wait(c->chopsticks))
		return (ret_error(1, "Error: phi_live - Sem wait failed.\n"));
	phi_set_status(c, pos, PICK, 1);
	if (sem_wait(c->chopsticks))
	{
		sem_post(c->chopsticks);
		return (ret_error(1, "Error: phi_live - Sem wait failed.\n"));
	}
	phi_set_status(c, pos, PICK, 1);
	if (sem_post(c->can_eat))
		return (ret_error(1, "Error: phi_live - Sem post failed.\n"));
	phi_set_status(c, pos, EAT, 1);
	++c->ate[pos];
	sleep_ms(c->time_to_eat);
	if (sem_post(c->chopsticks))
		return (ret_error(1, "Error: phi_live - Sem post failed.\n"));
	if (sem_post(c->chopsticks))
		return (ret_error(1, "Error: phi_live - Sem post failed.\n"));
	phi_set_status(c, pos, SLEEP, 1);
	sleep_ms(c->time_to_sleep);
	return (0);
}

static void	*s_live(void *args_v)
{
	t_args	*args;

	args = args_v;
	if (monitor_death_start(args))
		return (0);
	args->c->last_meal[args->pos] = get_time_ms(NULL);
	while (!args->c->dead && (!args->c->must_eat
		|| args->c->ate[args->pos] < args->c->must_eat))
	{
		if (s_live_routine(args->c, args->pos))
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
