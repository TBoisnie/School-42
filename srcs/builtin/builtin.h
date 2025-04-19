/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:16:53 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:07:18 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../environnement/env.h"
# include "../command/command.h"

int		is_builtin(t_cmd *cmd);
int		execute_builtin(t_cmd *cmd, t_env *env);

t_bool	is_valid_name(char *str);
char	*update_pwd(void);

int		builtin_cd(t_cmd *cmd, t_env *env);
int		builtin_echo(t_cmd *cmd, t_env *env);
int		builtin_env(t_cmd *cmd, t_env *env);
int		builtin_exit(t_cmd *cmd, t_env *env);
int		builtin_export(t_cmd *cmd, t_env *env);
int		builtin_pwd(t_cmd *cmd, t_env *env);
int		builtin_unset(t_cmd *cmd, t_env *env);

#endif
