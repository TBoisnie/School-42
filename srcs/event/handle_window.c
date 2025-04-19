/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:56:41 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 09:33:35 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../cube3d.h"
#include "event.h"

int	event_handle_window(void *params)
{
	t_config	*c;

	c = params;
	c->save = 0;
	mlx_destroy_window(c->mlx, c->window);
	exit_success();
	return (0);
}
