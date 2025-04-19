/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 22:51:08 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/06 03:21:14 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "config.h"

void	config_clear(t_config *c)
{
	sem_close(c->write_locker);
	sem_close(c->can_eat);
	sem_close(c->chopsticks);
	sem_close(c->death_locker);
	free(c->last_meal);
	free(c->ate);
	free(c->threads);
	free(c->death_monitors);
}
