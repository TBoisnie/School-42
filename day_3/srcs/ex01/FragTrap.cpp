/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:37:11 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:11:11 by tboisnie         ###   ########.fr       */
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
	: name(name),
	  level(1),
	  hit_points(100),
	  max_hit_points(100),
	  energy_points(100),
	  max_energy_points(100),
	  melee_attack_damage(30),
	  ranged_attack_damage(20),
	  armor_damage_reduction(5)
{
	std::cout
		<< "Heyyah!" << std::endl
		<< "Named constructor called." << std::endl;

	std::srand(std::time(NULL));
}

FragTrap::FragTrap(
	const FragTrap & other
)
{
	std::cout
		<< "Let's get this party started!" << std::endl
		<< "Copy constructor called." << std::endl;

	this->operator=(other);
}

FragTrap::~FragTrap()
{
	std::cout
		<< "RUN FOR YOUR LIIIIIVES!!!" << std::endl
		<< "Destructor called." << std::endl;
}

/**
 * Operators
 */
FragTrap &
FragTrap::operator=(
	const FragTrap & other
)
{
	std::cout
		<< "Recompiling my combat code!" << std::endl
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
FragTrap::rangedAttack(
	const std::string & target
)
{
	std::cout
		<< "Sniped!" << std::endl
		<< "FR4G-TP <" << this->name
		<< "> attaque <" << target
		<< "> à distance, causant <" << this->ranged_attack_damage
		<< "> points de dégâts !" << std::endl;
}

void
FragTrap::meleeAttack(
	const std::string & target
)
{
	std::cout
		<< "Meet professor punch!" << std::endl
		<< "FR4G-TP <" << this->name
		<< "> attaque <" << target
		<< "> au corps à corps, causant <" << this->melee_attack_damage
		<< "> points de dégâts !" << std::endl;
}

void
FragTrap::takeDamage(
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
		<< "Hit me, baby!" << std::endl
		<< "FR4G-TP <" << this->name
		<< "> prend <" << damage
		<< "> points de dégâts (HP=" << this->hit_points << ") !" << std::endl;
}

void
FragTrap::beRepaired(
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
		<< "Take these, gorgeous, you'll feel better!" << std::endl
		<< "FR4G-TP <" << this->name
		<< "> se soigne de <" << hit_restore
		<< "> points de vie (HP=" << this->hit_points << ") et restaure <" << energy_restore
		<< "> points d'energie (MP=" << this->energy_points << ") !" << std::endl;
}

void
FragTrap::vaulthunter_dot_exe(
	const std::string & target
)
{
	const unsigned int cost = 25;

	if (this->energy_points < cost)
	{
		std::cout
			<< "My assets... frozen!" << std::endl
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
