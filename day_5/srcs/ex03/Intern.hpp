/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 22:24:55 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 20:46:33 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include <string>
# include "Form.hpp"

class Intern
{
private:
	typedef struct	s_form
	{
		std::string name;
		Form * (*builder)(const std::string & target);
	}				t_form;

public:
	// Constructors & Destructors
	Intern();
	Intern(const Intern & other);
	~Intern();

	// Operators
	Intern & operator=(const Intern & other);

	// Methods
	Form * makeForm(const std::string & type, const std::string & target);

private:
	// Private methods
	static Form * presidentialPardonFormBuilder(const std::string & target);
	static Form * robotomyRequestFormBuilder(const std::string & target);
	static Form * shrubberyCreationFormBuilder(const std::string & target);
};

#endif