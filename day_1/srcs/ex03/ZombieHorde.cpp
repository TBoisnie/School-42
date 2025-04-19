/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ZombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 22:05:32 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:49:43 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include <cstdlib>
#include "ZombieHorde.hpp"

ZombieHorde::ZombieHorde(unsigned n)
{
	std::srand(std::time(NULL));
	this->size = n;
	this->zombies = new Zombie[n];
}

ZombieHorde::~ZombieHorde()
{
	delete[] this->zombies;
}

void
ZombieHorde::announce() const
{
	for (unsigned i = 0; i < this->size; i++)
		this->zombies[i].announce();
}