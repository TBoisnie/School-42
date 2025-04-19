/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:51:08 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/09 01:24:35 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "config.h"

void	config_clear(t_config *c)
{
	size_t	i;

	i = 0;
	while (i < c->number_of_philosopher)
		pthread_mutex_destroy(&c->chopsticks[i++]);
	pthread_mutex_destroy(&c->write_locker);
	free(c->last_meal);
	free(c->ate);
	free(c->chopsticks);
	free(c->threads);
	free(c->death_monitors);
}
