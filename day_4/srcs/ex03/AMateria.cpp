/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 22:22:06 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:09:58 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

/**
 * Constructors & Destructors
 */
AMateria::AMateria(
	std::string const & type
)
	: _xp(0),
	  type(type)
{
	// Empty
}

AMateria::AMateria(
	const AMateria & other
)
	: _xp(other.getXP()),
	  type(other.getType())
{
	// Empty
}

AMateria::~AMateria()
{
	// Empty
}

/**
 * Operators
 */
AMateria &
AMateria::operator=(
	const AMateria & other
)
{
	if (this != &other)
	{
		this->_xp = other._xp;
	}

	return *this;
}

/**
 * Methods
 */
void
AMateria::use(
	ICharacter & target
)
{
	(void)target;

	this->_xp += 10;
}

/**
 * Getters & Setters
 */
const std::string &
AMateria::getType() const
{
	return this->type;
}

unsigned int
AMateria::getXP() const
{
	return this->_xp;
}

void
AMateria::setXP(
	unsigned int xp
)
{
	this->_xp = xp;
}