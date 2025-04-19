/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:27:52 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 18:57:13 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <string>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form
{
private:
	const std::string name;
	bool signe;
	const int grade_signe;
	const int grade_execute;

private:
	Form();

public:
	// Constructors & Destructors
	Form(const std::string & name, int grade_signe, int grade_execute);
	Form(const Form & other);
	~Form();

	// Operators
	Form & operator=(const Form & other);

	// Methods
	void beSigned(const Bureaucrat & bureaucrat);

	// Getter & Setters
	const std::string & getName() const;
	int getSigne() const;
	int getGradeSigne() const;
	int getGradeExecute() const;

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
std::ostream & operator<<(std::ostream & out, const Form & form);

#endif