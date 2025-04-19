/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Squad.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 23:05:44 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 00:22:38 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUAD_HPP
# define SQUAD_HPP

# include "ISquad.hpp"

class Squad
	: public ISquad
{
private:
	// Attributes
	int count;
	int capacity;
	ISpaceMarine ** units_arr;

public:
	// Constructors & Destructors
	Squad();
	Squad(const Squad & other);
	~Squad();

	// Operators
	Squad & operator=(const Squad & other);

	// Methods
	int push(ISpaceMarine * unit);

	// Getters & Setters
	int getCount() const;
	ISpaceMarine * getUnit(int) const;

private:
	// Private Methods
	void clear();
	void reallocate();
};

#endif