/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 23:46:07 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/14 18:40:31 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <exception>

template<typename T>
class Array
{
private:
	T *_elements;
	unsigned int _size;

public:
	// Constructor & Destructors
	Array()
		: _elements(),
		  _size(0)
	{

	}

	Array(unsigned int size)
		: _elements(new T[size]),
		  _size(size)
	{

	}

	Array(const Array &other)
		: _elements()
		, _size(0)
	{
		this->operator=(other);
	}

	~Array()
	{
		if (this->_size > 0)
			delete[] this->_elements;
	}

	// Operators
	Array& operator=(const Array &other)
	{
		if (this != &other)
		{
			if (this->_size > 0)
				delete[] this->_elements;

			this->_size = other._size;
			this->_elements = new T[other._size];

			for (size_t i = 0; i < other._size; i++)
				this->_elements[i] = other._elements[i];
		}

		return *this;
	}

	T& operator[](unsigned int index)
	{
		if (index >= this->_size)
			throw std::exception();

		return this->_elements[index];
	}

	const T& operator[](unsigned int index) const
	{
		if (index >= this->_size)
			throw std::exception();

		return this->_elements[index];
	}

	// Methods

	// Getters & Setters
	unsigned int size() const
	{
		return this->_size;
	}
};

#endif