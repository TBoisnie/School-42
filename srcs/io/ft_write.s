# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_write.s                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 08:50:35 by tboisnie          #+#    #+#              #
#    Updated: 2020/02/09 20:27:34 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

%define CALL(fct_id)	0x0 | fct_id
%define WRITE			1

	extern	__errno_location

	global	ft_write

	section .text
ft_write:
	mov		rax, CALL(WRITE)
	syscall
	jl		error
	ret
error:
	neg		rax
	call	__errno_location
	mov		rax, -1
	ret