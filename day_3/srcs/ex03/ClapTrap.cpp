/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:28:31 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:16:25 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ClapTrap.hpp"

/**
 * Constructors & Destructors
 */
ClapTrap::ClapTrap(
	const std::string & name
)
	: name(name),
	  level(0),
	  hit_points(0),
	  max_hit_points(0),
	  energy_points(0),
	  max_energy_points(0),
	  melee_attack_damage(0),
	  ranged_attack_damage(0),
	  armor_damage_reduction(0)
{
	std::cout << "ClapTrap (Named constructor)." << std::endl;
}

ClapTrap::ClapTrap(
	const ClapTrap & other
)
{
	std::cout << "ClapTrap (Copy constructor)." << std::endl;

	this->operator=(other);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap (Destructor)." << std::endl;
}

/**
 * Operators
 */
ClapTrap &
ClapTrap::operator=(const ClapTrap & other)
{
	std::cout << "ClapTrap (Assignment operator)." << std::endl;

	if (this != &other)
	{
		this->name = other.name;
		this->level = other.level;
		this->hit_points = other.hit_points;
		this->max_hit_points = other.max_hit_points;
		this->energy_points = other.energy_points;
		this->max_energy_points = other.max_energy_points;
		this->melee_attack_damage = other.melee_attack_damage;
		this->ranged_attack_damage = other.ranged_attack_damage;
		this->armor_damage_reduction = other.armor_damage_reduction;
	}

	return *this;
}

/**
 * Methods
 */
void
ClapTrap::rangedAttack(
	const std::string & target
)
{
	std::cout
		<< "CL4P-TP <" << this->name
		<< "> attaque <" << target
		<< "> à distance, causant <" << this->ranged_attack_damage
		<< "> points de dégâts !" << std::endl;
}

void
ClapTrap::meleeAttack(
	const std::string & target
)
{
	std::cout
		<< "CL4P-TP <" << this->name
		<< "> attaque <" << target
		<< "> au corps à corps, causant <" << this->melee_attack_damage
		<< "> points de dégâts !" << std::endl;
}

void
ClapTrap::takeDamage(
	unsigned int amount
)
{
	unsigned int damage = 0;

	if (amount > this->armor_damage_reduction)
		damage = amount - this->armor_damage_reduction;

	if (this->hit_points >= damage)
		this->hit_points -= damage;
	else
		this->hit_points = 0;

	std::cout
		<< "CL4P-TP <" << this->name
		<< "> prend <" << damage
		<< "> points de dégâts (HP=" << this->hit_points << ") !" << std::endl;
}

void
ClapTrap::beRepaired(
	unsigned int amount
)
{
	const unsigned int hit_restore = amount;
	const unsigned int energy_restore = amount;

	this->hit_points += hit_restore;
	this->energy_points += energy_restore;

	if (this->hit_points > this->max_hit_points)
		this->hit_points = this->max_hit_points;
	if (this->energy_points > this->max_energy_points)
		this->energy_points = this->max_energy_points;

	std::cout
		<< "CL4P-TP <" << this->name
		<< "> se soigne de <" << hit_restore
		<< "> points de vie (HP=" << this->hit_points << ") et restaure <" << energy_restore
		<< "> points d'energie (MP=" << this->energy_points << ") !" << std::endl;
}