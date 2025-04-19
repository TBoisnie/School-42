/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:38:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 19:20:03 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

# include "Form.hpp"

class ShrubberyCreationForm
	: public Form
{
private:
	std::string target;

private:
	ShrubberyCreationForm();

public:
	// Constructors & Destructors
	ShrubberyCreationForm(const std::string & target);
	ShrubberyCreationForm(const ShrubberyCreationForm & other);
	~ShrubberyCreationForm();

	// Operators
	ShrubberyCreationForm & operator=(const ShrubberyCreationForm & other);

	// Methods
	void execute(const Bureaucrat & bureaucrat) const;
};

#endif