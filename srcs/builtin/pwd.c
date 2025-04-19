/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 17:15:29 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:03:43 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/param.h>
#include "libft/io/io.h"
#include "libft/memory/memory.h"
#include "builtin.h"

char	*update_pwd(void)
{
	static char	cwd[MAXPATHLEN];
	char		tmp[MAXPATHLEN];

	if (getcwd(tmp, sizeof(tmp)))
		mem_copy(cwd, tmp, MAXPATHLEN);
	return (cwd);
}

int		builtin_pwd(t_cmd *cmd, t_env *env)
{
	(void)cmd;
	(void)env;
	io_put_endl(update_pwd(), IO_OUT);
	return (0);
}
