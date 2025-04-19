/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 23:14:41 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/22 22:15:46 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

/**
 * Constructors & Destructors
 */
Character::Character(
	const std::string & name
)
	: name(name)
{
	for (int i = 0; i < Character::MAX_MATERIA; i++)
		this->materias[i] = NULL;
}

Character::Character(
	const Character & other
)
{
	for (int i = 0; i < Character::MAX_MATERIA; i++)
		this->materias[i] = NULL;

	this->operator=(other);
}

Character::~Character()
{
	for (int i = 0; i < Character::MAX_MATERIA; i++)
	{
		delete this->materias[i];
		this->materias[i] = NULL;
	}
}

/**
 * Operators
 */
Character &
Character::operator=(
	const Character & other
)
{
	if (this != &other)
	{
		this->name = other.name;

		for (int i = 0; i < Character::MAX_MATERIA; i++)
		{
			delete this->materias[i];
			this->materias[i] = NULL;

			if (other.materias[i])
				this->materias[i] = other.materias[i]->clone();
		}
	}

	return *this;
}

/**
 * Methods
 */
void
Character::equip(
	AMateria * materia
)
{
	for (int i = 0; i < Character::MAX_MATERIA; i++)
	{
		if (!this->materias[i])
		{
			this->materias[i] = materia;
			break;
		}
	}
}

void
Character::unequip(
	int index
)
{
	if (0 <= index && index < Character::MAX_MATERIA)
	{
		for ( ; index < Character::MAX_MATERIA - 1; ++index)
			this->materias[index] = this->materias[index + 1];

		this->materias[index] = NULL;
	}
}

void
Character::use(
	int index,
	ICharacter & target
)
{
	if (0 <= index && index < Character::MAX_MATERIA && this->materias[index])
		this->materias[index]->use(target);
}

/**
 * Getters & Setters
 */
const std::string &
Character::getName() const
{
	return this->name;
}

AMateria *
Character::getMateria(
	int index
)
{
	if (0 <= index && index < Character::MAX_MATERIA)
		return this->materias[index];

	return NULL;
}