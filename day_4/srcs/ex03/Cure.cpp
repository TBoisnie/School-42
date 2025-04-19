/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:59:32 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:14:43 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include "Cure.hpp"

/**
 * Constructors & Destructors
 */
Cure::Cure()
	: AMateria("cure")
{
	// Empty
}

Cure::Cure(
	const Cure & other
)
	: AMateria(other)
{
	// Empty
}

Cure::~Cure()
{
	// Empty
}

/**
 * Operators
 */
Cure &
Cure::operator=(
	const Cure & other
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
Cure::clone() const
{
	return new Cure(*this);
}

void
Cure::use(
	ICharacter & target
)
{
	AMateria::use(target);

	std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
