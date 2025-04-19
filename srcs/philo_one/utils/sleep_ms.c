/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 17:53:16 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/09 01:27:52 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "utils.h"

void	sleep_ms(time_t t)
{
	time_t	end;

	end = get_time_ms(NULL) + t;
	while (end > get_time_ms(NULL))
		usleep(50);
}
