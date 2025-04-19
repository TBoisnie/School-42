/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NinjaTrap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:37:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:15:41 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "NinjaTrap.hpp"

/**
 * Constructors & Destructors
 */
NinjaTrap::NinjaTrap(
	const std::string & name
)
	: ClapTrap(name)
{
	std::cout << "NinjaTrap (Named constructor)." << std::endl;

	this->level = 1;
	this->hit_points = 60;
	this->max_hit_points = 60;
	this->energy_points = 120;
	this->max_energy_points = 120;
	this->melee_attack_damage = 60;
	this->ranged_attack_damage = 5;
	this->armor_damage_reduction = 0;
}

NinjaTrap::NinjaTrap(
	const NinjaTrap & other
)
	: ClapTrap(other.name)
{
	std::cout << "NinjaTrap (Copy constructor)." << std::endl;

	this->operator=(other);
}

NinjaTrap::~NinjaTrap()
{
	std::cout << "NinjaTrap (Destructor)." << std::endl;
}

/**
 * Operators
 */
NinjaTrap &
NinjaTrap::operator=(
	const NinjaTrap & other
)
{
	std::cout << "NinjaTrap (Assignment operator)." << std::endl;

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
NinjaTrap::ninjaShoebox(const ClapTrap & clap)
{
	std::cout
		<< "Target disassembled!" << std::endl
		<< "NinjaTrap::ninjaShoebox(ClapTrap &)." << std::endl;

	(void)clap;
}

void
NinjaTrap::ninjaShoebox(const FragTrap & frag)
{
	std::cout
		<< "Punch punch! Fight!" << std::endl
		<< "NinjaTrap::ninjaShoebox(FragTrap &)." << std::endl;

	(void)frag;
}

void
NinjaTrap::ninjaShoebox(const ScavTrap & scav)
{
	std::cout
		<< "Pincer Attack!" << std::endl
		<< "NinjaTrap::ninjaShoebox(ScavTrap &)." << std::endl;

	(void)scav;
}

void
NinjaTrap::ninjaShoebox(const NinjaTrap & ninja)
{
	std::cout
		<< "Shoryuken!" << std::endl
		<< "NinjaTrap::ninjaShoebox(NinjaTrap &)." << std::endl;

	(void)ninja;
}