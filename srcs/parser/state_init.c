/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 21:28:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 21:39:43 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser.h"

void	parser_state_init(t_state *st)
{
	if (!st)
		return ;
	st->file_in = 0;
	st->file_out = 0;
	st->append = FALSE;
	st->word = NULL;
	st->error_code = 0;
	st->in_quote = 0;
}
