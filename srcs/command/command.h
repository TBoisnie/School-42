/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 22:23:02 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:09:59 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft/types.h"

typedef struct	s_cmd
{
	char			*name;
	char			**args;

	struct s_cmd	*piped;

	t_bool			append;
	char			*file_in;
	char			*file_out;

	t_bool			executable;
	int				exit_code;
}				t_cmd;

t_cmd			*cmd_new();
t_cmd			*cmd_delete(t_cmd *cmd);

t_cmd			*cmd_arg_add(t_cmd *cmd, char *arg);

t_bool			cmd_is_valid(t_cmd *cmd);

#endif
