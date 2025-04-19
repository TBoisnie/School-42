/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:40:06 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:35:59 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/io/io.h"
#include "separator.h"

int	redirect_in(t_cmd *cmd)
{
	int	file_flags;
	int	file_fd;

	file_flags = O_RDONLY;
	if ((file_fd = open(cmd->file_in, file_flags)) == -1)
	{
		io_put_err("Redirect_in: open() failed (no access or doesn't exist).");
		return (1);
	}
	if (dup2(file_fd, IO_IN) == -1)
	{
		close(file_fd);
		io_put_err("Redirect_in: dup2() failed.");
		return (1);
	}
	close(file_fd);
	return (0);
}
