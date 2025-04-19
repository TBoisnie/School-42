/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 15:22:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:13:25 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef char** t_env;

t_env	env_copy(char *envp[]);
t_env	env_clear(t_env env);
t_env	env_set(t_env env, char *str);
t_env	env_delete(t_env env, char *key);
char	*env_get(t_env env, char *key);

#endif
