/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 00:48:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/30 18:35:40 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "MutantStack.hpp"

int main()
{
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << "Top: " << mstack.top() << std::endl;

	mstack.pop();

	std::cout << "Size: " << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	std::cout << "Size: " << mstack.size() << std::endl;

	// Iterator
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--it;

	std::cout << "Iterator: ";
	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;

	// Reverse Iterator
	MutantStack<int>::reverse_iterator rit = mstack.rbegin();
	MutantStack<int>::reverse_iterator rite = mstack.rend();

	std::cout << "Reverse Iterator: ";
	while (rit != rite)
	{
		std::cout << *rit << " ";
		++rit;
	}
	std::cout << std::endl;

	// Copy
	MutantStack<int> cpy_1(mstack);
	MutantStack<int> cpy_2 = cpy_1;

	// Iterator on copy
	MutantStack<int>::iterator it1 = cpy_1.begin();
	MutantStack<int>::iterator ite1 = cpy_1.end();

	std::cout << "Iterator on copy: ";
	while (it1 != ite1)
	{
		std::cout << *it1 << " ";
		++it1;
	}
	std::cout << std::endl;

	return 0;
}
