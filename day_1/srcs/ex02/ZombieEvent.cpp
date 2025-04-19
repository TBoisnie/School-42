/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieEvent.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 18:55:53 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:47:26 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include <cstdlib>
#include "ZombieEvent.hpp"

ZombieEvent::ZombieEvent(std::string type)
	: type(type)
{
	std::srand(std::time(NULL));
}

void
ZombieEvent::setZombieType(std::string type)
{
	this->type = type;
}

Zombie*
ZombieEvent::newZombie(std::string name) const
{
	return new Zombie(this->type, name);
}

Zombie*
ZombieEvent::randomChump() const
{
	Zombie *zombie = new Zombie(type, getRandomName());

	zombie->announce();

	return zombie;
}

std::string
ZombieEvent::getRandomName() const
{
	std::string names[] = {
		"Michael Jackson",
		"Ed",
		"Solomon Grundy",
		"Jason Voorhees",
		"The Monster",
		"Liv Moore"
	};

	return names[std::rand() % (sizeof(names) / sizeof(names[0]))];
}
