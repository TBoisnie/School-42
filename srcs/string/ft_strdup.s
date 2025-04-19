# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_strdup.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 08:51:21 by tboisnie          #+#    #+#              #
#    Updated: 2020/02/09 08:51:23 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

	extern	ft_strlen
	extern	ft_strcpy
	extern	malloc

	global	ft_strdup

	section .text
ft_strdup:
	push	rdi
	call	ft_strlen
	inc		rax
	mov		rdi, rax
	call	malloc
	mov		rdi, rax
	pop		rsi
	call	ft_strcpy
	ret
