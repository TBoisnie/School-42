/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 18:38:19 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 19:16:25 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIAL_PARDON_FORM_HPP
# define PRESIDENTIAL_PARDON_FORM_HPP

# include "Form.hpp"

class PresidentialPardonForm
	: public Form
{
private:
	std::string target;

private:
	PresidentialPardonForm();

public:
	// Constructors & Destructors
	PresidentialPardonForm(const std::string & target);
	PresidentialPardonForm(const PresidentialPardonForm & other);
	~PresidentialPardonForm();

	// Operators
	PresidentialPardonForm & operator=(const PresidentialPardonForm & other);

	// Methods
	void execute(const Bureaucrat & bureaucrat) const;
};

#endif