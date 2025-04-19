/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 22:48:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/24 20:58:17 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <cstdlib>

template<typename T>
void
iter(T * arr, size_t size, void (*fun)(T &))
{
	for (size_t i = 0; i < size; ++i)
		fun(arr[i]);
}

#endif