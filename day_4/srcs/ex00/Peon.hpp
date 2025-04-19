/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Peon.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 20:51:09 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 01:33:11 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PEON_HPP
# define PEON_HPP

# include <string>
# include "Victim.hpp"

class Peon
	: public Victim
{
private:
	Peon();

public:
	// Constructors & Destructors
	Peon(const std::string & name);
	Peon(const Peon & other);
	~Peon();

	// Operators
	Peon & operator=(const Peon & other);

	// Methods
	void getPolymorphed() const;
};

#endif