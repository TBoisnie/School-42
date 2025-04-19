/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_is_clean.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 19:32:32 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 21:40:00 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_bool	parser_state_is_clean(t_state *st)
{
	if (!st)
		return (TRUE);
	return (!st->file_in && !st->file_out && !st->append && !st->word
		&& !st->error_code);
}
