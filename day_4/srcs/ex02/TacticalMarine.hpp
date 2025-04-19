/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TacticalMarine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 23:08:05 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 00:33:40 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TACTICAL_MARINE_HPP
# define TACTICAL_MARINE_HPP

#include "ISpaceMarine.hpp"

class TacticalMarine
	: public ISpaceMarine
{
public:
	// Constructors & Destructors
	TacticalMarine();
	TacticalMarine(const TacticalMarine & other);
	~TacticalMarine();

	// Operators
	TacticalMarine & operator=(const TacticalMarine & other);

	// Methods
	ISpaceMarine * clone() const;
	void battleCry() const;
	void rangedAttack() const;
	void meleeAttack() const;
};

#endif