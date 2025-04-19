/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 21:09:56 by tboisnie          #+#    #+#             */
/*   Updated: 2020/03/01 21:12:07 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHAR_H
# define CHAR_H

int	char_is_alnum(int c);
int	char_is_alpha(int c);
int	char_is_ascii(int c);
int	char_is_digit(int c);
int	char_is_print(int c);
int	char_is_space(int c);

int	char_to_lower(int c);
int	char_to_upper(int c);

#endif
