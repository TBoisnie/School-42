/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bs_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 20:01:33 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 21:31:59 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

unsigned	get_bs_count(char *str, char *end)
{
	unsigned	count;

	if (!str || !end)
		return (0);
	count = 0;
	while (end >= str && *end-- == '\\')
		count++;
	return (count);
}
