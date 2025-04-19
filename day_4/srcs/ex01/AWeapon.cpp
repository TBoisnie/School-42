/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWeapon.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:51:01 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 16:27:33 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AWeapon.hpp"

/**
 * Constructors & Destructors
 */
AWeapon::AWeapon(
	const std::string & name,
	int ap_cost,
	int damage
)
	: name(name)
	, ap_cost(ap_cost)
	, damage(damage)
{
	// Empty
}

AWeapon::AWeapon(
	const AWeapon & other
)
	: name(other.getName()),
	  ap_cost(other.getAPCost()),
	  damage(other.getDamage())
{
	// Empty
}

AWeapon::~AWeapon()
{
	// Empty
}

/**
 * Operators
 */
AWeapon &
AWeapon::operator=(
	const AWeapon & other
)
{
	if (this != &other)
	{
		this->setName(other.getName());
		this->setAPCost(other.getAPCost());
		this->setDamage(other.getDamage());
	}

	return *this;
}

/**
 * Methods
 */


/**
 * Getters & Setters
 */
const std::string &
AWeapon::getName() const
{
	return this->name;
}

int
AWeapon::getAPCost() const
{
	return this->ap_cost;
}

int
AWeapon::getDamage() const
{
	return this->damage;
}

void
AWeapon::setName(
	const std::string & name
)
{
	this->name = name;
}

void
AWeapon::setAPCost(
	int ap_cost
)
{
	this->ap_cost = ap_cost;
}

void
AWeapon::setDamage(
	int damage
)
{
	this->damage = damage;
}
