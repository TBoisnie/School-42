/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:28:30 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/09 16:47:07 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

time_t	get_time_ms(struct timeval *time)
{
	struct timeval	now;

	if (!time)
	{
		time = &now;
		if (gettimeofday(time, NULL))
			return (ret_error(0, "Error: get_time - gettimeofday failed.\n"));
	}
	return (time->tv_sec * 1000 + time->tv_usec / 1000);
}
