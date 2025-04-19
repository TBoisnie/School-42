/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:37:11 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:19:32 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "FragTrap.hpp"

/**
 * Constructors & Destructors
 */
FragTrap::FragTrap(
	const std::string & name
)
	: ClapTrap(name)
{
	std::cout << "FragTrap (Named constructor)." << std::endl;

	this->hit_points = 100;
	this->max_hit_points = 100;
	this->energy_points = 100;
	this->max_energy_points = 100;
	this->level = 1;
	this->melee_attack_damage = 30;
	this->ranged_attack_damage = 20;
	this->armor_damage_reduction = 5;

	std::srand(std::time(NULL));
}

FragTrap::FragTrap(
	const FragTrap & other
)
	: ClapTrap(other.name)
{
	std::cout << "FragTrap (Copy constructor)." << std::endl;

	this->operator=(other);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap (Destructor)." << std::endl;
}

/**
 * Operators
 */
FragTrap &
FragTrap::operator=(
	const FragTrap & other
)
{
	std::cout << "FragTrap (Assignment operator)." << std::endl;

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
FragTrap::vaulthunter_dot_exe(
	const std::string & target
)
{
	const unsigned int cost = 25;

	if (this->energy_points < cost)
	{
		std::cout
			<< "FR4G-TP <" << this->name
			<< "> n'a pas assez d'energie." << std::endl;
	}
	else
	{
		void (FragTrap::*arr_attack[])(const std::string&) = {
			&FragTrap::pauseAttack,
			&FragTrap::charmAttack,
			&FragTrap::magicAttack,
			&FragTrap::fakeAttack,
			&FragTrap::ccAttack
		};
		size_t size = sizeof(arr_attack) / sizeof(arr_attack[0]);

		this->energy_points -= cost;

		(this->*arr_attack[std::rand() % size])(target);
	}
}

/**
 * Private methods
 */
void
FragTrap::pauseAttack(
	const std::string & target
)
{
	std::cout
		<< "I feel a joke about poop decks coming on!" << std::endl
		<< "FR4G-TP <" << this->name
		<< "> fait une pause devant <" << target
		<< ">, causant <" << 0
		<< "> points de dégâts !" << std::endl;
}

void
FragTrap::charmAttack(
	const std::string & target
)
{
	std::cout
		<< "Roses are red and Violets are blue, wait... how many syllables was that?" << std::endl
		<< "FR4G-TP <" << this->name
		<< "> essai de charmer <" << target
		<< ">, causant <" << 0
		<< "> points de dégâts !" << std::endl;
}

void
FragTrap::magicAttack(
	const std::string & target
)
{
	std::cout
		<< "Beware! Danger!" << std::endl
		<< "FR4G-TP <" << this->name
		<< "> attaque <" << target
		<< "> avec sa magie, causant <" << this->ranged_attack_damage
		<< "> points de dégâts !" << std::endl;
}

void
FragTrap::fakeAttack(
	const std::string & target
)
{
	std::cout
		<< "I'm invisible!" << std::endl
		<< "FR4G-TP <" << this->name
		<< "> feinte une attaque <" << target
		<< "> causant <" << 0
		<< "> points de dégâts !" << std::endl;
}

void
FragTrap::ccAttack(
	const std::string & target
)
{
	std::cout
		<< "Calm down!" << std::endl
		<< "FR4G-TP <" << this->name
		<< "> etoudie <" << target
		<< "> causant <" << 0
		<< "> points de dégâts !" << std::endl;
}
