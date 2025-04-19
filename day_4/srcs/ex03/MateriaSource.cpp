/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 20:38:24 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:55:18 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

/**
 * Constructors & Destructors
 */
MateriaSource::MateriaSource()
{
	for (int i = 0; i < MateriaSource::MAX_LEARN; i++)
		this->materias[i] = NULL;
}


MateriaSource::MateriaSource(
	const MateriaSource & other
)
{
	for (int i = 0; i < MateriaSource::MAX_LEARN; i++)
		this->materias[i] = NULL;

	this->operator=(other);
}

MateriaSource::~MateriaSource()
{
	for (int i = 0; i < MateriaSource::MAX_LEARN; i++)
	{
		delete this->materias[i];
		this->materias[i] = NULL;
	}
}

/**
 * Operators
 */
MateriaSource &
MateriaSource::operator=(
	const MateriaSource & other
)
{
	if (this != &other)
	{
		for (int i = 0; i < MateriaSource::MAX_LEARN; i++)
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
MateriaSource::learnMateria(
	AMateria * materia
)
{
	if (!materia)
		return ;

	for (int i = 0; i < MateriaSource::MAX_LEARN; i++)
	{
		if (!this->materias[i])
		{
			this->materias[i] = materia->clone();
			break;
		}
	}
}

AMateria *
MateriaSource::createMateria(std::string const & type)
{
	for (int i = 0; i < MateriaSource::MAX_LEARN; i++)
	{
		if (this->materias[i] && this->materias[i]->getType().compare(type) == 0)
			return this->materias[i]->clone();
	}

	return NULL;
}
