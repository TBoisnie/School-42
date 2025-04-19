/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:40:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:12:00 by tboisnie         ###   ########.fr       */
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
	: name(name),
	  level(1),
	  hit_points(100),
	  max_hit_points(100),
	  energy_points(50),
	  max_energy_points(50),
	  melee_attack_damage(20),
	  ranged_attack_damage(15),
	  armor_damage_reduction(3)
{
	std::cout
		<< "Hello!" << std::endl
		<< "Named constructor called." << std::endl;

	std::srand(std::time(NULL));
}

ScavTrap::ScavTrap(
	const ScavTrap & other
)
{
	std::cout
		<< "You're an odd one." << std::endl
		<< "Copy constructor called." << std::endl;

	this->operator=(other);
}

ScavTrap::~ScavTrap()
{
	std::cout
		<< "​I'm free!" << std::endl
		<< "Destructor called." << std::endl;
}

/**
 * Operators
 */
ScavTrap &
ScavTrap::operator=(
	const ScavTrap & other
)
{
	std::cout
		<< "Somebody delivered a FEAST!!" << std::endl
		<< "Assignation operator called." << std::endl;

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
ScavTrap::rangedAttack(
	const std::string & target
)
{
	std::cout
		<< "Gotcha!" << std::endl
		<< "SC4V-TP <" << this->name
		<< "> attaque <" << target
		<< "> à distance, causant <" << this->ranged_attack_damage
		<< "> points de dégâts !" << std::endl;
}

void
ScavTrap::meleeAttack(
	const std::string & target
)
{
	std::cout
		<< "Karate chop!" << std::endl
		<< "SC4V-TP <" << this->name
		<< "> attaque <" << target
		<< "> au corps à corps, causant <" << this->melee_attack_damage
		<< "> points de dégâts !" << std::endl;
}

void
ScavTrap::takeDamage(
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
		<< "Pleasure in pain!" << std::endl
		<< "SC4V-TP <" << this->name
		<< "> prend <" << damage
		<< "> points de dégâts (HP=" << this->hit_points << ") !" << std::endl;
}

void
ScavTrap::beRepaired(
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
		<< "Gimme my hit points back!" << std::endl
		<< "SC4V-TP <" << this->name
		<< "> se soigne de <" << hit_restore
		<< "> points de vie (HP=" << this->hit_points << ") et restaure <" << energy_restore
		<< "> points d'energie (MP=" << this->energy_points << ") !" << std::endl;
}

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
