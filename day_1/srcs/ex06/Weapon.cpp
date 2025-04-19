/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 19:32:59 by tboisnie          #+#    #+#             */
/*   Updated: 2020/06/29 21:39:58 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type)
	: type(type)
{
}

const std::string&
Weapon::getType() const
{
	return this->type;
}

void
Weapon::setType(std::string type)
{
	this->type = type;
}

