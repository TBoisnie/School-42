/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:59:49 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 19:11:20 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PresidentialPardonForm.hpp"

/**
 * Constructors & Destructors
 */
PresidentialPardonForm::PresidentialPardonForm(
	const std::string & target
)
	: Form("PresidentialPardon", 25, 5)
	, target(target)
{
	// Empty
}

PresidentialPardonForm::PresidentialPardonForm(
	const PresidentialPardonForm & other
)
	: Form(other)
	, target(other.target)
{
	// Empty
}

PresidentialPardonForm::~PresidentialPardonForm()
{
	// Empty
}

/**
 *  Operators
 */
PresidentialPardonForm &
PresidentialPardonForm::operator=(
	const PresidentialPardonForm & other
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
PresidentialPardonForm::execute(
	const Bureaucrat & bureaucrat
) const
{
	Form::execute(bureaucrat);

	std::cout << this->target << " a été pardonnée par Zafod Beeblebrox." << std::endl;
}
