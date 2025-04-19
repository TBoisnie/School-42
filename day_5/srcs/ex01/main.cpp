/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:42:35 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 18:49:11 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

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
		std::cout << e.what() << std::endl;
	}

	try
	{
		Bureaucrat error("Nobody", 151);
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << "--------------------" << std::endl;

	Bureaucrat b_a("b_a", 25);
	Bureaucrat b_b("b_b", 5);

	Form form("A-38", 15, 1);

	std::cout << b_a;
	std::cout << b_b;
	std::cout << form;

	b_a.signForm(form);
	std::cout << form;
	b_b.signForm(form);
	std::cout << form;

	return 0;
}