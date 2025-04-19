/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 07:57:43 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/11 01:05:50 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
#include "event.h"

int	event_handle_key_pressed(int key, void *params)
{
	t_config	*c;

	c = params;
	if (key == KEY_ESC)
		exit_success();
	if (key == KEY_W)
		c->key_pressed[0] = 1;
	if (key == KEY_S)
		c->key_pressed[1] = 1;
	if (key == KEY_A)
		c->key_pressed[2] = 1;
	if (key == KEY_D)
		c->key_pressed[3] = 1;
	if (key == KEY_LEFT)
		c->key_pressed[4] = 1;
	if (key == KEY_RIGHT)
		c->key_pressed[5] = 1;
	return (0);
}

int	event_handle_key_released(int key, void *params)
{
	t_config	*c;

	c = params;
	if (key == KEY_W)
		c->key_pressed[0] = 0;
	if (key == KEY_S)
		c->key_pressed[1] = 0;
	if (key == KEY_A)
		c->key_pressed[2] = 0;
	if (key == KEY_D)
		c->key_pressed[3] = 0;
	if (key == KEY_LEFT)
		c->key_pressed[4] = 0;
	if (key == KEY_RIGHT)
		c->key_pressed[5] = 0;
	return (0);
}
