/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RadScorpion.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 20:57:50 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 18:11:55 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RadScorpion.hpp"

/**
 * Constructors & Destructors
 */
RadScorpion::RadScorpion()
	: Enemy(80, "RadScorpion")
{
	std::cout << "* click click click *" << std::endl;
}

RadScorpion::RadScorpion(
	const RadScorpion & other
)
	: Enemy(other)
{
	std::cout << "* click click click *" << std::endl;
}

RadScorpion::~RadScorpion()
{
	std::cout << "* SPROTCH *" << std::endl;
}

/**
 * Operators
 */
RadScorpion &
RadScorpion::operator=(
	const RadScorpion & other
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
RadScorpion::takeDamage(
	int damage
)
{
	Enemy::takeDamage(damage);
}
