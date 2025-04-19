/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 17:50:05 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/01 20:36:15 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "libft/io/io.h"
#include "separator.h"

int	redirect_out(t_cmd *cmd, int running)
{
	int	file_flags;
	int	file_rights;
	int	file_fd;

	file_flags = (cmd->append ? O_APPEND : O_TRUNC) | O_CREAT | O_WRONLY;
	file_rights = S_IRUSR | S_IWUSR;
	if ((file_fd = open(cmd->file_out, file_flags, file_rights)) == -1)
	{
		if (running)
			io_put_err("Redirect_out: open() failed (no access or doesn't \
			exist).");
		return (1);
	}
	if (running && dup2(file_fd, IO_OUT) == -1)
	{
		close(file_fd);
		io_put_err("Redirect_out: dup2() failed.");
		return (1);
	}
	close(file_fd);
	return (0);
}
