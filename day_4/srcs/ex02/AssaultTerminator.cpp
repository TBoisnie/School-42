/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssaultTerminator.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:33:46 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 00:40:33 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "AssaultTerminator.hpp"

/**
 * Constructors & Destructors
 */
AssaultTerminator::AssaultTerminator()
{
	std::cout << "* teleports from space *" << std::endl;
}

AssaultTerminator::AssaultTerminator(
	const AssaultTerminator & other
)
{
	this->operator=(other);
}

AssaultTerminator::~AssaultTerminator()
{
	std::cout << "I’ll be back ..." << std::endl;
}

/**
 * Operators
 */
AssaultTerminator &
AssaultTerminator::operator=(
	const AssaultTerminator & other
)
{
	if (this != &other)
		std::cout << "* teleports from space *" << std::endl;

	return *this;
}

/**
 * Methods
 */
ISpaceMarine *
AssaultTerminator::clone() const
{
	return new AssaultTerminator(*this);
}

void
AssaultTerminator::battleCry() const
{
	std::cout << "This code is unclean. Purify it !" << std::endl;
}

void
AssaultTerminator::rangedAttack() const
{
	std::cout << "* does nothing *" << std::endl;
}

void
AssaultTerminator::meleeAttack() const
{
	std::cout << "* attaque with chainfists *" << std::endl;
}
