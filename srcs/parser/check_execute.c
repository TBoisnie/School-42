/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:25:21 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/02 22:15:17 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/io/io.h"
#include "libft/array/array.h"
#include "libft/string/string.h"
#include "builtin/builtin.h"
#include "environnement/env.h"
#include "parser.h"

static char	*try_with_path(t_cmd *cmd, char **path_split, size_t i)
{
	char		*exe_new;
	char		*tmp;
	struct stat data;

	if (!(exe_new = str_join(path_split[i], "/")))
	{
		io_put_err("Check_execute: str_join() failed.");
		return (NULL);
	}
	tmp = exe_new;
	if (!(exe_new = str_join(exe_new, cmd->name)))
	{
		free(tmp);
		io_put_err("Check_execute: str_join() failed.");
		return (NULL);
	}
	free(tmp);
	if (stat(exe_new, &data) != -1 && data.st_mode & S_IXUSR)
		return (exe_new);
	free(exe_new);
	return (NULL);
}

static void	update_cmd(t_cmd *cmd, char *exe_new)
{
	if (exe_new)
	{
		free(cmd->name);
		cmd->name = exe_new;
	}
	else
		cmd->executable = FALSE;
}

t_cmd		*check_execute(t_cmd *cmd, t_env env)
{
	char		*exe_new;
	char		*path;
	char		**path_split;
	struct stat	data;
	size_t		i;

	if (!cmd || !cmd->name || *(cmd->name) == '/' || is_builtin(cmd) ||
		(stat(cmd->name, &data) != -1 && data.st_mode & S_IXUSR))
		return (cmd);
	path_split = NULL;
	exe_new = NULL;
	if ((path = env_get(env, "PATH")))
		if (!(path_split = str_split(path, ':')))
			io_put_err("Check_execute: str_split() failed.");
	i = 0;
	while (path_split && path_split[i])
	{
		if ((exe_new = try_with_path(cmd, path_split, i)))
			break ;
		i++;
	}
	arr_str_clear(path_split);
	update_cmd(cmd, exe_new);
	return (cmd);
}
