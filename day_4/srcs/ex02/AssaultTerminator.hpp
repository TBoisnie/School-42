/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AssaultTerminator.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 23:11:01 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 00:39:06 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSAULT_TERMINATOR_HPP
# define ASSAULT_TERMINATOR_HPP

#include "ISpaceMarine.hpp"

class AssaultTerminator
	: public ISpaceMarine
{
public:
	// Constructors & Destructors
	AssaultTerminator();
	AssaultTerminator(const AssaultTerminator & other);
	~AssaultTerminator();

	// Operators
	AssaultTerminator & operator=(const AssaultTerminator & other);

	// Methods
	ISpaceMarine * clone() const;
	void battleCry() const;
	void rangedAttack() const;
	void meleeAttack() const;
};

#endif