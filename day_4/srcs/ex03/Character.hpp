/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:39:01 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 15:20:47 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include <string>
# include "ICharacter.hpp"
# include "AMateria.hpp"

class Character
	: public ICharacter
{
	static const int MAX_MATERIA = 4;

private:
	// Attributes
	std::string name;
	AMateria * materias[MAX_MATERIA];

private:
	Character();

public:
	// Constructors & Destructors
	Character(const std::string & name);
	Character(const Character & other);
	~Character();

	// Operators
	Character & operator=(const Character & other);

	// Methods
	void equip(AMateria * materia);
	void unequip(int index);
	void use(int index, ICharacter & target);

	// Getters & Setters
	const std::string & getName() const;
	AMateria * getMateria(int index);
};

#endif