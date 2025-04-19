/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Sorcerer.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 20:50:59 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 01:31:23 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORCERER_HPP
# define SORCERER_HPP

# include <iostream>
# include <string>
# include "Victim.hpp"

class Sorcerer
{
private:
	// Attributes
	std::string name;
	std::string title;

private:
	Sorcerer();

public:
	// Constructors & Destructors
	Sorcerer(const std::string & name, const std::string & title);
	Sorcerer(const Sorcerer & other);
	~Sorcerer();

	// Operators
	Sorcerer& operator=(const Sorcerer & other);

	// Methods
	void polymorph(const Victim & victim) const;

	// Getters & Setters
	const std::string & getName() const;
	const std::string & getTitle() const;
};

// Overload
std::ostream & operator<<(std::ostream & out, const Sorcerer & obj);

#endif