/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pony.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 20:32:18 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/28 01:29:42 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pony.hpp"

int Pony::count = 0;

int
Pony::getCount()
{
	return Pony::count;
}

Pony::Pony(std::string name, std::string color)
	: name(name), color(color), energy(50), ran(0)
{
	Pony::count++;
}

Pony::~Pony()
{
	Pony::count--;
}

const std::string
Pony::getName() const
{
	return this->name;
}

const std::string
Pony::getColor() const
{
	return this->color;
}

int
Pony::getEnergy() const
{
	return this->energy;
}

int
Pony::getRan() const
{
	return this->ran;
}

void
Pony::run()
{
	if (this->energy >= 10)
	{
		this->ran += 20;
		this->energy -= 10;
	}
}

void
Pony::rest()
{
	if (this->energy <= 70)
	{
		this->energy += 30;
	}
}

