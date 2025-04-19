/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 06:15:05 by tboisnie          #+#    #+#             */
/*   Updated: 2020/02/08 18:08:32 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "string/string.h"
#include "cube3d.h"

void	exit_success(void)
{
	exit(0);
}

void	exit_error(char *message)
{
	write(2, message, str_length(message) * sizeof(char));
	write(2, "\n", sizeof(char));
	exit(0);
}
