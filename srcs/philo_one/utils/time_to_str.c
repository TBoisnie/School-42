/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 01:39:01 by tboisnie          #+#    #+#             */
/*   Updated: 2020/11/09 01:27:20 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*time_to_str(char *str, time_t number)
{
	if (number > 9)
		str = time_to_str(str, number / 10);
	*str = '0' + (number % 10);
	*++str = '\0';
	return (str);
}
