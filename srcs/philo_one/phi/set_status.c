/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:30:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/05 20:40:14 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pthread.h>
#include "utils/utils.h"
#include "phi.h"

static char	*message_append_status(t_phi_status s, char *cursor)
{
	char	*str;

	str = NULL;
	if (s == PICK)
		str = " has taken a fork";
	else if (s == EAT)
		str = " is eating";
	else if (s == SLEEP)
		str = " is sleeping";
	else if (s == THINK)
		str = " is thinking";
	else if (s == DIE)
		str = " died";
	return (mem_copy(cursor, str, str_length(str)));
}

static void	s_set_message(char *cursor, time_t timestamp, size_t pos,
	t_phi_status s)
{
	cursor = time_to_str(cursor, timestamp);
	cursor = mem_copy(cursor, "\t", 1);
	cursor = time_to_str(cursor, (time_t)pos + 1);
	cursor = message_append_status(s, cursor);
	cursor = mem_copy(cursor, "\n", 2);
}

void		phi_set_status(t_config *c, size_t pos, t_phi_status s, int lock)
{
	char			message[256];
	time_t			now;

	if (lock && pthread_mutex_lock(&c->write_locker))
	{
		ret_error(0, "Error: phi_status - Mutex lock failed.\n");
		return ;
	}
	if (c->dead > 0)
	{
		if (lock && pthread_mutex_unlock(&c->write_locker))
			ret_error(0, "Error: phi_status - Mutex unlock failed.\n");
		return ;
	}
	now = get_time_ms(NULL);
	if (s == EAT)
		c->last_meal[pos] = now;
	else if (s == DIE)
		c->dead = 1;
	s_set_message(message, now - c->started_at, pos, s);
	write(1, message, str_length(message));
	if (lock && pthread_mutex_unlock(&c->write_locker))
		ret_error(0, "Error: phi_status - Mutex unlock failed.\n");
}
