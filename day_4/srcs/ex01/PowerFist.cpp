/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PowerFist.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:26:47 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 17:11:50 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PowerFist.hpp"

/**
 * Constructors & Destructors
 */
PowerFist::PowerFist()
	: AWeapon("Power Fist", 8, 50)
{
	// Empty
}

PowerFist::PowerFist(
	const PowerFist & other
)
	: AWeapon(other)
{
	// Empty
}

PowerFist::~PowerFist()
{
	// Empty
}

/**
 * Operators
 */
PowerFist &
PowerFist::operator=(const PowerFist & other)
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
PowerFist::attack() const
{
	std::cout << "* pschhh... SBAM! *" << std::endl;
}
