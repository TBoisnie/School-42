/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 21:21:43 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 18:26:24 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Character.hpp"

/**
 * Constructors & Destructors
 */
Character::Character(
	const std::string & name
)
	: name(name)
	, ap(40)
	, weapon()
{
	// Empty
}

Character::Character(
	const Character & other
)
	: name(other.name),
	  ap(other.ap),
	  weapon(other.weapon)
{
	// Empty
}

Character::~Character()
{
	// Empty
}

/**
 * Operators
 */
Character &
Character::operator=(
	const Character & other
)
{
	if (this == &other)
	{
		this->name = other.name;
		this->ap = other.ap;
		this->weapon = other.weapon;
	}

	return *this;
}

/**
 * Methods
 */
void
Character::recoverAP()
{
	this->ap += 10;

	if (this->ap > 40)
		this->ap = 40;
}

void
Character::equip(AWeapon *weapon)
{
	this->weapon = weapon;
}

void
Character::attack(
	Enemy * enemy
)
{
	if (!weapon || !enemy || this->ap < this->weapon->getAPCost())
		return;

	this->ap -= this->weapon->getAPCost();

	std::cout
		<< this->name << " attaque " << enemy->getType() << " with a "
		<< this->weapon->getName() << std::endl;

	this->weapon->attack();

	enemy->takeDamage(this->weapon->getDamage());
	if (enemy->getHP() <= 0)
		delete enemy;
}

/**
 * Getters & Setters
 */
const std::string &
Character::getName() const
{
	return this->name;
}

const AWeapon *
Character::getWeapon() const
{
	return this->weapon;
}

int
Character::getAP() const
{
	return this->ap;
}

/**
 * Overload
 */
std::ostream &
operator<<(
	std::ostream & out,
	const Character & character
)
{
	out << character.getName() << " has " << character.getAP() << " AP and ";

	if (character.getWeapon())
		out << "carries a " << character.getWeapon()->getName();
	else
		out << "is unarmed";

	out << std::endl;

	return out;
}