/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 18:53:39 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:14:52 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include "easyfind.hpp"

int main( void )
{
	std::vector<int> vec;
	std::deque<int> deq;
	std::list<int> lst;

	for (int i = -5; i < 5; i++)
	{
		vec.push_back(i);
		vec.push_back(-i);

		deq.push_back(i);
		deq.push_back(-i);

		lst.push_back(i);
		lst.push_back(-i);
	}

	// Show default
	std::cout << "Vector :";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Deque :\t";
	for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "List :\t";
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	// Vector
	easyfind<std::vector<int> >(vec, -4) = 999;
	easyfind<std::vector<int> >(vec, 2) = 999;

	try
	{
		easyfind<std::vector<int> >(vec, 10) = 999;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception : " << e.what() << std::endl;
	}

	// Deque
	easyfind<std::deque<int> >(deq, -4) = 999;
	easyfind<std::deque<int> >(deq, 2) = 999;

	try
	{
		easyfind<std::deque<int> >(deq, 10) = 999;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception : " << e.what() << std::endl;
	}

	// List
	easyfind<std::list<int> >(lst, -4) = 999;
	easyfind<std::list<int> >(lst, 2) = 999;

	try
	{
		easyfind<std::list<int> >(lst, 10) = 999;
	}
	catch (std::exception & e)
	{
		std::cout << "Exception : " << e.what() << std::endl;
	}

	// Show modified
	std::cout << "Vector :";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "Deque :\t";
	for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "List :\t";
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	return 0;
}
