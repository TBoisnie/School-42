/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 20:23:06 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/05 19:32:50 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "monitor.h"
#include "phi/phi.h"
#include "utils/utils.h"

static void	*s_death(void *args_v)
{
	t_args	*args;

	args = args_v;
	while (!args->c->dead && (!args->c->must_eat
		|| args->c->ate[args->pos] < args->c->must_eat))
	{
		if (sem_wait(args->c->write_locker))
		{
			ret_error(0, "Error: s_death - Sem lock failed.\n");
		}
		if (args->c->last_meal[args->pos] + args->c->time_to_die
			< get_time_ms(NULL))
		{
			phi_set_status(args->c, args->pos, DIE, 0);
		}
		if (sem_post(args->c->write_locker))
		{
			ret_error(0, "Error: s_death - Sem unlock failed.\n");
		}
		sleep_ms(1);
	}
	return (0);
}

int			monitor_death_start(t_args *args)
{
	if (pthread_create(&args->c->death_monitors[args->pos],
		NULL, s_death, args))
		return (ret_error(1, "Error: death_m - pthread create failed.\n"));
	return (0);
}
