# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_read.s                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 08:49:49 by tboisnie          #+#    #+#              #
#    Updated: 2020/02/09 20:26:59 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

%define CALL(fct_id)	0x0 | fct_id
%define READ			0

	extern	__errno_location

	global	ft_read

	section	.text
ft_read:
	mov		rax, CALL(READ)
	syscall
	jl		error
	ret
error:
	neg		rax
	call	__errno_location
	mov		rax, -1
	ret