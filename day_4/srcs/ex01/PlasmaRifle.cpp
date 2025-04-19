/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlasmaRifle.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:03:41 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 17:07:52 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PlasmaRifle.hpp"

/**
 * Constructors & Destructors
 */
PlasmaRifle::PlasmaRifle()
	: AWeapon("Plasma Rifle", 5, 21)
{
	// Empty
}

PlasmaRifle::PlasmaRifle(
	const PlasmaRifle & other
)
	: AWeapon(other)
{
	// Empty
}

PlasmaRifle::~PlasmaRifle()
{
	// Empty
}

/**
 * Operators
 */
PlasmaRifle &
PlasmaRifle::operator=(
	const PlasmaRifle & other
)
{
	if (this != &other)
	{
		AWeapon::operator=(other);
	}

	return *this;
}

/**
 * Methods
 */
void
PlasmaRifle::attack() const
{
	std::cout << "* piouuu piouuu piouuu *" << std::endl;
}
