/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:33:25 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 17:18:08 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Enemy.hpp"

/**
 * Constructors & Destructors
 */

Enemy::Enemy(
	int hp,
	const std::string & type
)
	: type(type)
	, hp(hp)
{
	// Empty
}

Enemy::Enemy(
	const Enemy & other
)
	: type(other.getType())
	, hp(other.getHP())
{
	// Empty
}

Enemy::~Enemy()
{
	// Empty
}

/**
 * Operators
 */
Enemy &
Enemy::operator=(
	const Enemy & other
)
{
	if (this != &other)
	{
		this->setType(other.getType());
		this->setHP(other.getHP());
	}

	return *this;
}

/**
 * Methods
 */
void
Enemy::takeDamage(
	int damage
)
{
	if (damage >= 0)
		this->hp -= damage;
}


/**
 * Getters & Setters
 */
const std::string &
Enemy::getType() const
{
	return this->type;
}

int
Enemy::getHP() const
{
	return this->hp;
}

void
Enemy::setType(
	const std::string & type
)
{
	this->type = type;
}

void
Enemy::setHP(
	int hp
)
{
	this->hp = hp;
}