/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 22:24:51 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 20:46:25 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

/**
 * Constructors & Destructors
 */
Intern::Intern()
{
	// Empty
}

Intern::Intern(const Intern & other)
{
	this->operator=(other);
}

Intern::~Intern()
{
	// Empty
}

/**
 * Operators
 */
Intern &
Intern::operator=(
	const Intern & other
)
{
	if (this != &other)
	{
		// Empty
	}

	return *this;
}

/**
 * Methods
 */
Form *
Intern::makeForm(
	const std::string & type,
	const std::string & target
)
{
	t_form	forms[] = {
		{"presidential pardon", presidentialPardonFormBuilder},
		{"shrubbery creation", shrubberyCreationFormBuilder},
		{"robotomy request", robotomyRequestFormBuilder},
	};

	for (size_t i = 0; i < sizeof(forms) / sizeof(forms[0]); ++i)
	{
		if (forms[i].name == type)
		{
			std::cout << "Intern creates " << type << std::endl;

			return forms[i].builder(target);
		}
	}

	std::cout << "Type de formulaire non connu." << std::endl;

	return NULL;
}

/**
 * Private Methods
 */
Form *
Intern::presidentialPardonFormBuilder(
	const std::string & target
)
{
	return new PresidentialPardonForm(target);
}

Form *
Intern::robotomyRequestFormBuilder(
	const std::string & target
)
{
	return new RobotomyRequestForm(target);
}

Form *
Intern::shrubberyCreationFormBuilder(
	const std::string & target
)
{
	return new ShrubberyCreationForm(target);
}