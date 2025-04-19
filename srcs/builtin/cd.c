/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 15:13:02 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:05:55 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/param.h>
#include "libft/io/io.h"
#include "libft/array/array.h"
#include "libft/string/string.h"
#include "libft/memory/memory.h"
#include "builtin.h"

static char	*get_cwd_var(char *str, char *var_name)
{
	char *cwd;

	cwd = update_pwd();
	mem_copy(str, cwd, str_length(cwd) + 1);
	mem_move(&str[str_length(var_name)], str, str_length(str) + 1);
	mem_copy(str, var_name, str_length(var_name));
	return (str);
}

static char	*get_dir(t_cmd *cmd, t_env *env)
{
	char	*dir;

	dir = NULL;
	if (arr_str_length(cmd->args) > 2)
	{
		io_put_err("Builtin_cd: Too many arguments.");
		cmd->exit_code = 1;
	}
	else if (arr_str_length(cmd->args) == 1 && !(dir = env_get(*env, "HOME")))
	{
		io_put_err("Builtin_cd: HOME variable is not set.");
		cmd->exit_code = 1;
	}
	else if (!dir && !str_n_cmp(cmd->args[1], "-", 2)
		&& !(dir = env_get(*env, "OLDPWD")))
	{
		io_put_err("Builtin_cd: OLDPWD variable is not set.");
		cmd->exit_code = 1;
	}
	else if (!dir)
		dir = cmd->args[1];
	return (dir);
}

int			builtin_cd(t_cmd *cmd, t_env *env)
{
	char	oldpwd[MAXPATHLEN + 7 + 1];
	char	pwd[MAXPATHLEN + 4 + 1];
	char	*dir;

	if (!(dir = get_dir(cmd, env)))
		return (cmd->exit_code);
	get_cwd_var(oldpwd, "OLDPWD=");
	if (chdir(dir))
	{
		io_put_err("Builtin_cd: chdir() failed (no access or doesn't exist).");
		return (1);
	}
	get_cwd_var(pwd, "PWD=");
	*env = env_set(*env, oldpwd);
	*env = env_set(*env, pwd);
	return (0);
}
