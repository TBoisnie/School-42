/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:01:15 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 18:50:13 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

/**
 * Constructors & Destructors
 */
Form::Form(
	const std::string & name,
	int grade_signe,
	int grade_execute
)
	: name(name)
	, signe(false)
	, grade_signe(grade_signe)
	, grade_execute(grade_execute)
{
	if (grade_signe < Bureaucrat::GRADE_MIN || grade_execute < Bureaucrat::GRADE_MIN)
		throw Form::GradeTooHighException();
	else if (grade_signe > Bureaucrat::GRADE_MAX || grade_execute > Bureaucrat::GRADE_MAX)
		throw Form::GradeTooLowException();
}

Form::Form(
	const Form & other
)
	: name(other.name),
	  signe(other.signe),
	  grade_signe(other.grade_signe),
	  grade_execute(other.grade_execute)
{
	// Empty
}

Form::~Form()
{
	// Empty
}

/**
 * Operators
 */
Form &
Form::operator=(
	const Form & other
)
{
	if (this != &other)
	{
		this->signe = other.getSigne();
	}

	return *this;
}

/**
 * Methods
 */
void
Form::beSigned(
	const Bureaucrat & bureaucrat
)
{
	if (bureaucrat.getGrade() > this->grade_signe)
		throw GradeTooLowException();

	this->signe = true;
}


/**
 * Getters & Setters
 */
const std::string &
Form::getName() const
{
	return this->name;
}

int
Form::getSigne() const
{
	return this->signe;
}

int
Form::getGradeSigne() const
{
	return this->grade_signe;
}

int
Form::getGradeExecute() const
{
	return this->grade_execute;
}

/**
 * Nested
 */

// GradeTooHighException
const char *
Form::GradeTooHighException::what() const throw()
{
	return "Form::GradeTooHighException";
}

// GradeTooLowException
const char *
Form::GradeTooLowException::what() const throw()
{
	return "Form::GradeTooLowException";
}

/**
 * Overload
 */
std::ostream &
operator<<(
	std::ostream & out,
	const Form & form
)
{
	out
		<< "<" << form.getName() << ">, form requires grade <"
		<< form.getGradeSigne() << "> to be signed and grade <"
		<< form.getGradeExecute() << "> to be executed, and signed = "
		<< form.getSigne()
		<< std::endl;

	return out;
}