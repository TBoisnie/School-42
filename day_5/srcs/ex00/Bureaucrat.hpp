/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 19:42:29 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 17:16:08 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <string>
# include <iostream>
# include <exception>

class Bureaucrat
{
	static const int GRADE_MIN = 1;		// Highest
	static const int GRADE_MAX = 150;	// Lowest

private:
	// Attributes
	const std::string name;
	int grade;

private:
	Bureaucrat();

public:
	// Constructors & Destructors
	Bureaucrat(const std::string & name, int grade);
	Bureaucrat(const Bureaucrat & other);
	~Bureaucrat();

	// Operators
	Bureaucrat & operator=(const Bureaucrat & other);

	// Methods
	void upgrade();
	void downgrade();

	// Getters & Setters
	const std::string & getName() const;
	int getGrade() const;

	// Nested Exceptions
	class GradeTooHighException
		: public std::exception
	{
	public:
		// Methods
		const char* what() const throw();
	};

	class GradeTooLowException
		: public std::exception
	{
	public:
		// Methods
		const char* what() const throw();
	};
};

// Overload
std::ostream & operator<<(std::ostream & out, const Bureaucrat & bureaucrat);

#endif