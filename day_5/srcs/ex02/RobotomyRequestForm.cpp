/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:59:49 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 19:19:07 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RobotomyRequestForm.hpp"

/**
 * Constructors & Destructors
 */
RobotomyRequestForm::RobotomyRequestForm(
	const std::string & target
)
	: Form("RobotomyRequest", 72, 45),
	  target(target)
{
	// Empty
}

RobotomyRequestForm::RobotomyRequestForm(
	const RobotomyRequestForm & other
)
	: Form(other),
	  target(other.target)
{
	// Empty
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	// Empty
}

/**
 *  Operators
 */
RobotomyRequestForm &
RobotomyRequestForm::operator=(
	const RobotomyRequestForm & other
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
RobotomyRequestForm::execute(
	const Bureaucrat & bureaucrat
) const
{
	Form::execute(bureaucrat);
	std::cout << "*Bruit de perceuse* " << this->target << " a été robotomizé." << std::endl;
}
