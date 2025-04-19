/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:42:35 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 19:28:20 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	Bureaucrat	boss("Boss", 1);
	Bureaucrat	employe_a("Employe A", 150);
	Bureaucrat	employe_b("Employe B", 46);
	ShrubberyCreationForm	sc_form("TreeHouse"); // 145, 137
	RobotomyRequestForm		rr_form("Clank"); // 72, 45
	PresidentialPardonForm	pp_form("MrPresident"); // 25, 5

	// Presentation
	std::cout << boss;
	std::cout << employe_a;
	std::cout << employe_b;
	std::cout << std::endl;
	std::cout << sc_form;
	std::cout << rr_form;
	std::cout << pp_form;
	std::cout << std::endl;

	// Signe and Execute FAIL
	employe_a.signForm(sc_form);
	employe_a.executeForm(sc_form);

	// Signe and Execute with Upgrade
	employe_b.signForm(sc_form);
	employe_b.executeForm(sc_form);
	employe_b.signForm(rr_form);
	employe_b.executeForm(rr_form);
	employe_b.upgrade();
	employe_b.executeForm(rr_form);

	// Execute and Signe FAIL order
	boss.executeForm(pp_form);
	boss.signForm(pp_form);
	boss.executeForm(pp_form);

	// Forms
	std::cout << std::endl;
	std::cout << employe_b;
	std::cout << std::endl;
	std::cout << sc_form;
	std::cout << rr_form;
	std::cout << pp_form;
	std::cout << std::endl;

	// Upgrade and Downgrade FAIL
	try
	{
		boss.upgrade();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		employe_a.downgrade();
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}