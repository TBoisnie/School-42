# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_strlen.s                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/09 08:51:28 by tboisnie          #+#    #+#              #
#    Updated: 2020/02/09 20:28:28 by tboisnie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

	global	ft_strlen

	section .text
ft_strlen:
	xor		rax, rax
	dec		rax
while:
	inc		rax
	cmp		byte [rdi + rax], 0
	jne		while
	ret
