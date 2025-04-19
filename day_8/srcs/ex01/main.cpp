/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 20:07:16 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 01:14:34 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "span.hpp"

#define N 100000
#define TRY_INSERT N + 1

int main( void )
{
	std::srand(std::time(NULL));

	{
		Span s(N);

		std::cout << "-- Load Random Numbers --" << std::endl;

		for (unsigned int i = 0; i < TRY_INSERT; ++i)
		{
			try
			{
				s.addNumber(std::rand());
			}
			catch (std::exception &e)
			{
				std::cout << "Exception : " << e.what() << std::endl;
			}
		}

		std::cout << "-- Span --" << std::endl;
		std::cout << "Longest : " << s.longestSpan() << std::endl;
		std::cout << "Shortest : " << s.shortestSpan() << std::endl;
	}

	{
		Span s(N);

		std::cout << "-- Load Consecutive Numbers --" << std::endl;

		for (unsigned int i = 0; i < TRY_INSERT; ++i)
		{
			try
			{
				s.addNumber(static_cast<int>(i));
			}
			catch (std::exception &e)
			{
				std::cout << "Exception : " << e.what() << std::endl;
			}
		}

		std::cout << "-- Span --" << std::endl;
		std::cout << "Longest : " << s.longestSpan() << std::endl;
		std::cout << "Shortest : " << s.shortestSpan() << std::endl;
	}

	{
		std::vector<int> v;
		v.push_back(-100);
		v.push_back(35);
		v.push_back(0);
		v.push_back(100);
		v.push_back(10);

		Span s(v.size());

		std::cout << "-- Load Defined Numbers --" << std::endl;

		try
		{
			s.addRange(v.begin(), v.end());
		}
		catch (std::exception &e)
		{
			std::cout << "Exception : " << e.what() << std::endl;
		}

		std::cout << "-- Span --" << std::endl;
		std::cout << "Longest : " << s.longestSpan() << std::endl;
		std::cout << "Shortest : " << s.shortestSpan() << std::endl;
	}

	return 0;
}
