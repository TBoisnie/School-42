/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 18:35:47 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:42:55 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Zombie.hpp"

int Zombie::alive = 0;

Zombie::Zombie(std::string type, std::string name)
	: type(type), name(name)
{
	Zombie::alive++;
}

Zombie::~Zombie()
{
	Zombie::alive--;
}

void
Zombie::announce() const
{
	std::cout << "<" << this->name << " (" << this->type << ")> is HUNGRYYYY!" << std::endl;
}
