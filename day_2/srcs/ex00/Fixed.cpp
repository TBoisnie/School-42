/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:50:40 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/03 18:46:38 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

const int Fixed::bits = 8;

Fixed::Fixed()
	: value(0)
{
	std::cout << "Default constructor called." << std::endl;
}

Fixed::Fixed(const Fixed &other)
{
	std::cout << "Copy constructor called." << std::endl;

	this->operator=(other);
}

Fixed&
Fixed::operator=(const Fixed &other)
{
	std::cout << "Assignation operator called." << std::endl;

	if (this != &other)
	{
		this->value = other.getRawBits();
	}

	return *this;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called." << std::endl;
}

int
Fixed::getRawBits() const
{
	std::cout << "getRawBits member function called." << std::endl;

	return this->value;
}

void
Fixed::setRawBits(const int raw)
{
	this->value = raw;
}