/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 15:50:40 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/03 19:05:45 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include "Fixed.hpp"

/**
 * Attributes
 */
const int Fixed::bits = 8;

/**
 * Static
 */
Fixed&
Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b) ? a : b;
}

Fixed&
Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b) ? a : b;
}

const Fixed&
Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b) ? a : b;
}

const Fixed&
Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b) ? a : b;
}

/**
 * Constructors & Destructors
 */
// Default (Rule of 3)
Fixed::Fixed()
	: value(0)
{
	std::cout << "Default constructor called." << std::endl;
}

// Copy (Rule of 3)
Fixed::Fixed(const Fixed &other)
{
	std::cout << "Copy constructor called." << std::endl;

	this->operator=(other);
}

Fixed::Fixed(const int n)
{
	this->value = n << Fixed::bits;
}

Fixed::Fixed(const float f)
{
	this->value = roundf(f * (1 << Fixed::bits));
}

Fixed::~Fixed()
{
	std::cout << "Destructor called." << std::endl;
}

/**
 * Operators
 */
// Assignation (Rule of 3)
Fixed&
Fixed::operator=(const Fixed &other)
{
	std::cout << "Assignation operator called." << std::endl;

	if (this != &other)
		this->value = other.getRawBits();

	return *this;
}

Fixed
Fixed::operator+(const Fixed &rhs) const
{
	return Fixed(toFloat() + rhs.toFloat());
}

Fixed
Fixed::operator-(const Fixed &rhs) const
{
	return Fixed(toFloat() - rhs.toFloat());
}

Fixed
Fixed::operator*(const Fixed &rhs) const
{
	return Fixed(toFloat() * rhs.toFloat());
}

Fixed
Fixed::operator/(const Fixed &rhs) const
{
	return Fixed(toFloat() / rhs.toFloat());
}

Fixed&
Fixed::operator++()
{
	++this->value;

	return *this;
}

Fixed&
Fixed::operator--()
{
	--this->value;

	return *this;
}

Fixed
Fixed::operator++(int)
{
	Fixed copy(*this);

	operator++();

	return copy;
}

Fixed
Fixed::operator--(int)
{
	Fixed copy(*this);

	operator--();

	return copy;
}

bool
Fixed::operator==(const Fixed &rhs) const
{
	return (this->value == rhs.value);
}

bool
Fixed::operator!=(const Fixed &rhs) const
{
	return (this->value != rhs.value);
}

bool
Fixed::operator<=(const Fixed &rhs) const
{
	return (this->value <= rhs.value);
}
bool
Fixed::operator>=(const Fixed &rhs) const
{
	return (this->value >= rhs.value);
}

bool
Fixed::operator<(const Fixed &rhs) const
{
	return (this->value < rhs.value);
}

bool
Fixed::operator>(const Fixed &rhs) const
{
	return (this->value > rhs.value);
}

std::ostream&
operator<<(std::ostream &out, const Fixed &obj)
{
	out << obj.toFloat();

	return out;
}

/**
 * Methods
 */
int
Fixed::toInt() const
{
	return (int)this->value >> Fixed::bits;
}

float
Fixed::toFloat() const
{
	return (float)this->value / (1 << Fixed::bits);
}

/**
 * Getters & Setters
 */
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