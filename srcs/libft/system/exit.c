/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 15:20:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/02 18:46:39 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../io/io.h"
#include "system.h"

void	sys_exit(int code, char *message)
{
	if (message)
		io_put_err(message);
	exit(code);
}
