/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperTrap.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 17:58:40 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:40:24 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "SuperTrap.hpp"

/**
 * Constructors & Destructors
 */
SuperTrap::SuperTrap(
	const std::string & name
)
	: ClapTrap(name)
	, FragTrap("")
	, NinjaTrap("")
{
	std::cout << "SuperTrap (Named constructor)." << std::endl;

	this->level = 1;
	this->hit_points = FragTrap::hit_points;
	this->max_hit_points = FragTrap::max_hit_points;
	this->energy_points = NinjaTrap::energy_points;
	this->max_energy_points = NinjaTrap::max_energy_points;
	this->melee_attack_damage = NinjaTrap::melee_attack_damage;
	this->ranged_attack_damage = FragTrap::ranged_attack_damage;
	this->armor_damage_reduction = FragTrap::armor_damage_reduction;
}

SuperTrap::SuperTrap(
	const SuperTrap & other
)
	: ClapTrap(other.name)
	, FragTrap("")
	, NinjaTrap("")
{
	std::cout << "SuperTrap (Copy constructor)." << std::endl;

	this->operator=(other);
}

SuperTrap::~SuperTrap()
{
	std::cout << "SuperTrap (Destructor)." << std::endl;
}

/**
 * Operators
 */
SuperTrap &
SuperTrap::operator=(const SuperTrap & other)
{
	std::cout << "SuperTrap (Assignment operator)." << std::endl;

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
SuperTrap::rangedAttack(
	const std::string & target
)
{
	FragTrap::rangedAttack(target);
}

void
SuperTrap::meleeAttack(
	const std::string & target
)
{
	NinjaTrap::meleeAttack(target);
}