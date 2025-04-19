/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Victim.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:39:59 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/22 15:05:26 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Victim.hpp"

/**
 * Constructors & Destructors
 */
Victim::Victim(
	const std::string & name
)
	: name(name)
{
	std::cout << "A random victim called " << this->name << " just appeared!" << std::endl;
}

Victim::Victim(
	const Victim & other
)
{
	this->operator=(other);

	std::cout << "A random victim called " << this->name << " just appeared!" << std::endl;
}

Victim::~Victim()
{
	std::cout << "The victim " << this->name << " died for no apparent reasons!" << std::endl;
}

/**
 * Operators
 */
Victim &
Victim::operator=(
	const Victim & other
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
Victim::getPolymorphed() const
{
	std::cout << this->name << " was just polymorphed in a cute little sheep!" << std::endl;
}

/**
 * Getters & Setters
 */
const std::string &
Victim::getName() const
{
	return this->name;
}

/**
 * Overload
 */
std::ostream &
operator<<(
	std::ostream & out,
	const Victim & victim
)
{
	out << "I'm " << victim.getName() << " and I like otters!" << std::endl;

	return out;
}