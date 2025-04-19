/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:40:34 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:36:20 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATOR_H
# define SEPARATOR_H

# include "libft/types.h"
# include "command/command.h"

int	redirect_in(t_cmd *cmd);
int	redirect_out(t_cmd *cmd, int running);

#endif
