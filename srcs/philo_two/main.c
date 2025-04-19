/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:36:51 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/09 01:55:12 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "config/config.h"
#include "monitor/monitor.h"
#include "phi/phi.h"
#include "utils/utils.h"

static t_args	*s_init_args(t_config *c)
{
	t_args	*args_arr;
	size_t	i;

	if (!(args_arr = malloc(sizeof(t_args) * c->number_of_philosopher)))
	{
		ret_error(1, "Error: run - Malloc failed.\n");
		return (NULL);
	}
	i = 0;
	while (i < c->number_of_philosopher)
	{
		args_arr[i].c = c;
		args_arr[i].pos = i;
		++i;
	}
	return (args_arr);
}

static int		run(t_config *c)
{
	t_args	*args_arr;

	if (!(args_arr = s_init_args(c)))
		return (1);
	if (phi_live_start(c, args_arr))
	{
		free(args_arr);
		return (1);
	}
	if (phi_live_wait(c))
	{
		free(args_arr);
		return (1);
	}
	free(args_arr);
	return (0);
}

int				main(int ac, char *av[])
{
	t_config	c;
	int			err;

	if (ac < 5 || ac > 6)
		return (ret_error(1, "Error: main - Invalid number of arguments.\n"));
	if (config_init(&c, ac, av))
		return (1);
	err = run(&c);
	config_clear(&c);
	return (err);
}
