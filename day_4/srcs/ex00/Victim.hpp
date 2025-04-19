/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Victim.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 20:51:05 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 01:55:04 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VICTIM_HPP
# define VICTIM_HPP

# include <iostream>
# include <string>

class Victim
{
protected:
	// Attributes
	std::string name;

private:
	Victim();

public:
	// Constructors & Destructors
	Victim(const std::string & name);
	Victim(const Victim & other);
	virtual ~Victim();

	// Operators
	Victim & operator=(const Victim & other);

	// Methods
	virtual void getPolymorphed() const;

	// Getters & Setters
	const std::string & getName() const;
};

// Overload
std::ostream & operator<<(std::ostream & out, const Victim & victim);

#endif