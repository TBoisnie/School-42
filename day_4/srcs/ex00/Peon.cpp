/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Peon.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:54:16 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/22 15:03:42 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Peon.hpp"

/**
 * Constructors & Destructors
 */
Peon::Peon(
	const std::string & name
)
	: Victim(name)
{
	std::cout << "Zog zog." << std::endl;
}

Peon::Peon(
	const Peon & other
)
	: Victim(other)
{
	std::cout << "Zog zog." << std::endl;
}

Peon::~Peon()
{
	std::cout << "Bleuark..." << std::endl;
}

/**
 * Operators
 */
Peon &
Peon::operator=(
	const Peon & other
)
{
	if (this != &other)
	{
		this->name = other.name;
	}

	return *this;
}

/**
 * Methods
 */
void
Peon::getPolymorphed() const
{
	std::cout << this->name << " was just polymorphed into a pink pony!" << std::endl;
}
