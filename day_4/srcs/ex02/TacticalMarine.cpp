/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TacticalMarine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:26:20 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 00:37:41 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "TacticalMarine.hpp"

/**
 * Constructors & Destructors
 */
TacticalMarine::TacticalMarine()
{
	std::cout << "Tactical Marine ready for action !" << std::endl;
}

TacticalMarine::TacticalMarine(
	const TacticalMarine & other
)
{
	this->operator=(other);
}

TacticalMarine::~TacticalMarine()
{
	std::cout << "Aaargh ..." << std::endl;
}

/**
 * Operators
 */
TacticalMarine &
TacticalMarine::operator=(
	const TacticalMarine & other
)
{
	if (this != &other)
		std::cout << "Tactical Marine ready for action !" << std::endl;

	return *this;
}

/**
 * Methods
 */
ISpaceMarine *
TacticalMarine::clone() const
{
	return new TacticalMarine(*this);
}

void
TacticalMarine::battleCry() const
{
	std::cout << "For the Holy PLOT !" << std::endl;
}

void
TacticalMarine::rangedAttack() const
{
	std::cout << "* attacks with a bolter *" << std::endl;
}

void
TacticalMarine::meleeAttack() const
{
	std::cout << "* attacks with a chainsword *" << std::endl;
}
