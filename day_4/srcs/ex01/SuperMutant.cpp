/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperMutant.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 20:58:07 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 18:07:31 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "SuperMutant.hpp"

/**
 * Constructors & Destructors
 */
SuperMutant::SuperMutant()
	: Enemy(170, "Super Mutant")
{
	std::cout << "Gaaah. Break everything !" << std::endl;
}

SuperMutant::SuperMutant(
	const SuperMutant & other
)
	: Enemy(other)
{
	std::cout << "Gaaah. Break everything !" << std::endl;
}

SuperMutant::~SuperMutant()
{
	std::cout << "Aaargh ..." << std::endl;
}

/**
 * Operators
 */
SuperMutant &
SuperMutant::operator=(
	const SuperMutant & other
)
{
	if (this != &other)
	{
		Enemy::operator=(other);
	}

	return *this;
}

/**
 * Methods
 */
void
SuperMutant::takeDamage(
	int damage
)
{
	Enemy::takeDamage(damage - 3);
}
