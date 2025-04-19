/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 18:39:55 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:59:52 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASY_FIND_HPP
# define EASY_FIND_HPP

# include <algorithm>
# include <stdexcept>

template<
	typename T
>
int &
easyfind(
	T & ctn,
	int value
)
{
	typename T::iterator found = std::find(ctn.begin(), ctn.end(), value);

	if (found == ctn.end())
		throw std::runtime_error("Easyfind() : value not found.");

	return *found;
}

#endif
