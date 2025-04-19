/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 20:07:01 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 00:44:22 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "span.hpp"

/**
 * Constructors & Destructors
 */
Span::Span(
	unsigned int N
)
	: max_size(N)
{
	this->values.reserve(N);
}

Span::Span(
	const Span & other
)
	: max_size(other.max_size)
	, values(other.values)
{
	// Empty
}

Span::~Span()
{
	// Empty
}

/**
 * Operators
 */
Span &
Span::operator=(
	const Span & other
)
{
	if (this == &other)
		return *this;

	this->max_size = other.max_size;
	this->values = other.values;

	return *this;
}

/**
 * Methods
 */
void
Span::addNumber(
	int n
)
{
	if (this->values.size() >= this->max_size)
		throw std::runtime_error("Span::AddNumber() : Span container is full.");

	this->values.push_back(n);
}

long
Span::shortestSpan()
{
	if (this->values.size() < 2)
		throw std::runtime_error("Span::ShortestSpan() : Not enought values.");

	std::sort(this->values.begin(), this->values.end());

	long current;
	long min = static_cast<long>(this->values[1]) - static_cast<long>(this->values[0]);

	for (std::vector<int>::iterator it = this->values.begin() + 2; it != this->values.end(); ++it)
	{
		current = static_cast<long>(*it) - static_cast<long>(*(it - 1));

		if (current < min) min = current;
	}

	return (min);
}

long
Span::longestSpan()
{
	if (this->values.size() < 2)
		throw std::runtime_error("LongesteSpan() : Not enought values.");

	int min = *min_element(this->values.begin(), this->values.end());
	int max = *max_element(this->values.begin(), this->values.end());

	return static_cast<long>(max) - static_cast<long>(min);
}
 