/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 22:20:06 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/24 20:56:49 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template<typename T>
void
swap(T & a, T & b)
{
	const T tmp(a);

	a = b;
	b = tmp;
}

template<typename T>
const T &
min(const T & a, const T & b)
{
	return (a < b) ? a : b;
}

template<typename T>
const T &
max(const T & a, const T & b)
{
	return (a > b) ? a : b;
}

#endif
