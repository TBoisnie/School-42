/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 07:50:03 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/22 13:52:29 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# define OS 1

# if OS == 0
#  define KEY_ESC	53
#  define KEY_W		13
#  define KEY_S		1
#  define KEY_A		0
#  define KEY_D		2
#  define KEY_LEFT	123
#  define KEY_RIGHT	124
# else
#  define KEY_ESC	65307
#  define KEY_W		119
#  define KEY_S		115
#  define KEY_A		97
#  define KEY_D		100
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
# endif

int	event_handle_key_pressed(int key, void *params);
int	event_handle_key_released(int key, void *params);
int	event_handle_loop(t_config *c);
int	event_handle_window(void *params);

#endif
