/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:03:33 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/02 18:16:27 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "command/command.h"
# include "environnement/env.h"

int	execute_pipe(t_cmd *cmd, t_env env);
int	execute_no_pipe(t_cmd *cmd, t_env *env);
int	execute(t_cmd *cmd, t_env *env);

#endif
