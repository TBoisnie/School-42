/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:38:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 19:17:00 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOTOMY_REQUEST_FORM_HPP
# define ROBOTOMY_REQUEST_FORM_HPP

# include "Form.hpp"

class RobotomyRequestForm
	: public Form
{
private:
	std::string target;

private:
	RobotomyRequestForm();

public:
	// Constructors & Destructors
	RobotomyRequestForm(const std::string & target);
	RobotomyRequestForm(const RobotomyRequestForm & other);
	~RobotomyRequestForm();

	// Operators
	RobotomyRequestForm & operator=(const RobotomyRequestForm & other);

	// Methods
	void execute(const Bureaucrat & bureaucrat) const;
};

#endif