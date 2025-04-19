/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:42:32 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 19:27:13 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

/**
 * Constructors & Destructors
 */
Bureaucrat::Bureaucrat(
	const std::string & name,
	int grade
)
	: name(name)
{
	if (grade < Bureaucrat::GRADE_MIN)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > Bureaucrat::GRADE_MAX)
		throw Bureaucrat::GradeTooLowException();

	this->grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat & other)
	: name(other.name),
	  grade(other.grade)
{
	// Empty
}

Bureaucrat::~Bureaucrat()
{
	// Empty
}

/**
 * Operators
 */
Bureaucrat &
Bureaucrat::operator=(
	const Bureaucrat & other
)
{
	if (this != &other)
	{
		this->grade = other.grade;
	}

	return *this;
}

/**
 * Methods
 */
void
Bureaucrat::upgrade()
{
	if (this->grade <= Bureaucrat::GRADE_MIN)
		throw Bureaucrat::GradeTooHighException();

	this->grade--;
}

void
Bureaucrat::downgrade()
{
	if (this->grade >= Bureaucrat::GRADE_MAX)
		throw Bureaucrat::GradeTooLowException();

	this->grade++;
}

void
Bureaucrat::signForm(
	Form & form
) const
{
	try
	{
		form.beSigned(*this);
		std::cout << this->name << " signs " << form.getName() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << this->name << " can't sign " << form.getName() << " because " << e.what() << std::endl;
	}
}

void
Bureaucrat::executeForm(
	const Form & form
)
{
	try
	{
		form.execute(*this);
		std::cout << this->name << " executes " << form.getName() << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cout << this->name << " can't execute " << form.getName() << " because " << e.what() << std::endl;
	}
}

/**
 * Getters & Setters
 */
const std::string &
Bureaucrat::getName() const
{
	return this->name;
}

int
Bureaucrat::getGrade() const
{
	return this->grade;
}

/**
 * Nested
 */

// GradeTooHighException
const char *
Bureaucrat::GradeTooHighException::what() const throw()
{
	return "GradeTooHighException";
}

// GradeTooLowException
const char *
Bureaucrat::GradeTooLowException::what() const throw()
{
	return "GradeTooLowException";
}

/**
 * Overload
 */
std::ostream &
operator<<(
	std::ostream & out,
	const Bureaucrat & bureaucrat
)
{
	out
		<< "<" << bureaucrat.getName() << ">, bureaucrat grade <"
		<< bureaucrat.getGrade() << ">" <<  std::endl;

	return out;
}