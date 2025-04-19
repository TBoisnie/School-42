# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_strcpy.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 08:51:10 by tboisnie          #+#    #+#              #
#    Updated: 2020/02/09 08:51:13 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

	global	ft_strcpy

	section .text
ft_strcpy:
	mov		rdx, rdi
while:
	mov		rax, [rsi]
	mov		[rdi], rax
	cmp		byte [rsi], 0
	je		return
	inc		rsi
	inc		rdi
	jmp		while
return:
	mov		rax, rdx
	ret
