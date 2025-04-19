/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:40:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:23:02 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "ScavTrap.hpp"

/**
 * Constructors & Destructors
 */
ScavTrap::ScavTrap(
	const std::string & name
)
	: ClapTrap(name)
{
	std::cout << "ScavTrap (Named constructor)." << std::endl;

	this->level = 1;
	this->hit_points = 100;
	this->max_hit_points = 100;
	this->energy_points = 50;
	this->max_energy_points = 50;
	this->melee_attack_damage = 20;
	this->ranged_attack_damage = 15;
	this->armor_damage_reduction = 3;

	std::srand(std::time(NULL));
}

ScavTrap::ScavTrap(
	const ScavTrap & other
)
	: ClapTrap(other.name)
{
	std::cout << "ScavTrap (Copy constructor)." << std::endl;

	this->operator=(other);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap (Destructor)." << std::endl;
}

/**
 * Operators
 */
ScavTrap &
ScavTrap::operator=(
	const ScavTrap & other
)
{
	std::cout << "ScavTrap (Assignment operator)." << std::endl;

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
ScavTrap::challengeNewcomer()
{
	std::string challenges[] = {
		"Keep It in Family : Kill COV with COV weapons.",
		"Interplanetary Ninja Chatterbox : Find ECHO logs describing how the FR4G-TP Prototype was created.",
		"Hammerlock's Occult Hunt : Hunt down the legendary Yeti."
	};
	size_t size = sizeof(challenges) / sizeof(challenges[0]);

	std::cout << challenges[rand() % size] << std::endl;
}
