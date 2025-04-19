/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 16:23:12 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/24 20:36:11 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "iter.hpp"

void mul_2(int & n)
{
	n *= 2;
}

void to_lower(char & c)
{
	if (c >= 'A' && c <= 'Z')
		c = c - 'A' + 'a';
}

template<typename T>
void
addTwo(T & v)
{
	v += 2;
}

int main( void )
{
	// Int
	int values[] = {0, 1, 2, 3, 4, 5};

	for (size_t i = 0; i < 6; i++)
		std::cout << values[i] << " ";
	std::cout << std::endl;

	iter(values, 6, mul_2);

	for (size_t i = 0; i < 6; i++)
		std::cout << values[i] << " ";
	std::cout << std::endl;

	iter(values, 6, addTwo<int>);

	for (size_t i = 0; i < 6; i++)
		std::cout << values[i] << " ";
	std::cout << std::endl;

	// Char
	char str[] = "This IS a WEiRd SenTEnCE.";

	std::cout << str << std::endl;
	iter(str, 25, to_lower);
	std::cout << str << std::endl;
	iter(str, 25, addTwo<char>);
	std::cout << str << std::endl;

	return 0;
}