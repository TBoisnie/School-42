/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:42:35 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 17:39:03 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat boss("Boss", 1);
	Bureaucrat employe("Employe", 150);

	std::cout << boss;
	std::cout << employe;

	try
	{
		boss.upgrade();
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		employe.downgrade();
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		Bureaucrat error("Nobody", 0);
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	try
	{
		Bureaucrat error("Nobody", 151);
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}