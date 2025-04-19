/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:26:58 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/03 01:53:19 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Human.hpp"

std::string
Human::identify() const
{
	return this->brain.identify();
}

const Brain&
Human::getBrain() const
{
	return this->brain;
}