# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_strcmp.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 08:50:58 by tboisnie          #+#    #+#              #
#    Updated: 2020/02/09 08:51:04 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

	global	ft_strcmp

	section .text
ft_strcmp:
	xor		rcx, rcx
while:
	mov		dl, byte [rdi + rcx]
	mov		bl, byte [rsi + rcx]
	cmp		dl, 0
	je		return
	inc		rcx
	cmp		dl, bl
	je		while
return:
	sub		dl, bl
	movsx	rax, dl
	ret