/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:38:35 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:17:54 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Ice.hpp"

/**
 * Constructors & Destructors
 */
Ice::Ice()
	: AMateria("ice")
{
	// Empty
}

Ice::Ice(
	const Ice & other
)
	: AMateria(other)
{
	// Empty
}

Ice::~Ice()
{
	// Empty
}

/**
 * Operators
 */
Ice &
Ice::operator=(
	const Ice & other
)
{
	if (this != &other)
	{
		this->setXP(other.getXP());
	}

	return *this;
}

/**
 * Methods
 */
AMateria *
Ice::clone() const
{
	return new Ice(*this);
}

void
Ice::use(
	ICharacter & target
)
{
	AMateria::use(target);

	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
