/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sorcerer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 20:58:29 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/22 15:04:44 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sorcerer.hpp"

/**
 * Constructors & Destructors
 */
Sorcerer::Sorcerer(
	const std::string & name,
	const std::string & title
)
	: name(name)
	, title(title)
{
	std::cout
		<< this->name << ", " << this->title
		<< ", is born!" << std::endl;
}

Sorcerer::Sorcerer(
	const Sorcerer & other
)
{
	this->operator=(other);

	std::cout
		<< this->name << ", " << this->title
		<< ", is born!" << std::endl;
}

Sorcerer::~Sorcerer()
{
	std::cout
		<< this->name << ", " << this->title
		<< ", is dead! Consequences will never be the same!" << std::endl;
}

/**
 * Operators
 */
Sorcerer &
Sorcerer::operator=(
	const Sorcerer & other
)
{
	if (this != &other)
	{
		this->name = other.name;
		this->title = other.title;
	}

	return *this;
}

/**
 * Methods
 */
void
Sorcerer::polymorph(
	const Victim & victim
) const
{
	victim.getPolymorphed();
}

/**
 * Getters & Setters
 */
const std::string &
Sorcerer::getName() const
{
	return this->name;
}

const std::string &
Sorcerer::getTitle() const
{
	return this->title;
}

/**
 * Overload
 */
std::ostream &
operator<<(
	std::ostream & out,
	const Sorcerer & sorcerer
)
{
	out
		<< "I am " << sorcerer.getName() << ", " << sorcerer.getTitle()
		<< ", and I like ponies!" << std::endl
	;

	return out;
}