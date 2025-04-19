/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:59:49 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 19:28:49 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include "ShrubberyCreationForm.hpp"

/**
 * Constructors & Destructors
 */
ShrubberyCreationForm::ShrubberyCreationForm(
	const std::string & target
)
	: Form("ShrubberyCreation", 145, 137),
	  target(target)
{
	// Empty
}

ShrubberyCreationForm::ShrubberyCreationForm(
	const ShrubberyCreationForm & other
)
	: Form(other),
	  target(other.target)
{
	// Empty
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	// Empty
}

/**
 *  Operators
 */
ShrubberyCreationForm &
ShrubberyCreationForm::operator=(
	const ShrubberyCreationForm & other
)
{
	if (this != &other)
	{
		Form::operator=(other);
		this->target = other.target;
	}

	return *this;
}

/**
 * Methods
 */
void
ShrubberyCreationForm::execute(
	const Bureaucrat & bureaucrat
) const
{
	Form::execute(bureaucrat);

	std::ofstream file_out((this->target + "_shrubbery").c_str());

	if (!file_out.is_open())
		return ;

	file_out
		<< "      /\\" << std::endl
		<< "     /\\*\\" << std::endl
		<< "    /\\O\\*\\" << std::endl
		<< "   /*/\\/\\/\\" << std::endl
		<< "  /\\O\\/\\*\\/\\" << std::endl
		<< " /\\*\\/\\*\\/\\/\\" << std::endl
		<< "/\\O\\/\\/*/\\/O/\\" << std::endl
		<< "      ||" << std::endl
		<< "      ||" << std::endl
		<< "      ||" << std::endl
		<< std::endl;

	file_out.close();
}
