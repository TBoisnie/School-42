/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 19:10:00 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:18:58 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../memory/memory.h"
#include "../array.h"

char	**arr_str_new(size_t size)
{
	return (mem_calloc(size + 1, sizeof(char *)));
}
