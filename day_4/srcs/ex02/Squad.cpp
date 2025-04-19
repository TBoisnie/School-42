/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Squad.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 23:18:50 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 01:32:26 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include "Squad.hpp"

/**
 * Constructors & Destructors
 */
Squad::Squad()
	: count(0)
	, capacity(8)
	, units_arr()
{
	this->units_arr = new ISpaceMarine*[this->capacity];
}

Squad::Squad(
	const Squad & other
)
	: count(0)
	, capacity(8)
	, units_arr()
{
	this->units_arr = new ISpaceMarine*[this->capacity];
	this->operator=(other);
}

Squad::~Squad()
{
	this->clear();

	delete[] this->units_arr;
}

/**
 * Operators
 */
Squad &
Squad::operator=(
	const Squad & other
)
{
	if (this != &other)
	{
		this->clear();

		for (int i = 0; i < other.getCount(); ++i)
			this->push(other.getUnit(i)->clone());
	}

	return *this;
}

/**
 * Methods
 */
int
Squad::push(
	ISpaceMarine * unit
)
{
	if (!unit)
		return 0;

	for (int i = 0; i < this->getCount(); ++i)
	{
		if (unit == this->getUnit(i))
			return 0;
	}

	this->reallocate();

	this->units_arr[this->count++] = unit;

	return this->count;
}

/**
 * Getters & Setters
 */
int
Squad::getCount() const
{
	return this->count;
}

ISpaceMarine *
Squad::getUnit(
	int n
) const
{
	if (n < 0 || n >= this->getCount())
		return NULL;

	return this->units_arr[n];
}

/**
 * Private methods
 */
void
Squad::clear()
{
	for (int i = 0; i < this->getCount(); ++i)
	{
		delete this->units_arr[i];
		this->units_arr[i] = NULL;
	}
	this->count = 0;
}

void
Squad::reallocate()
{
	static const int mult = 2;

	if (this->getCount() >= this->capacity)
	{
		ISpaceMarine ** tmp_units_arr = new ISpaceMarine*[this->capacity * mult];

		this->capacity *= mult;

		for (int i = 0; i < this->getCount(); ++i)
		{
			tmp_units_arr[i] = this->getUnit(i);
		}

		delete[] this->units_arr;

		this->units_arr = tmp_units_arr;
	}
}