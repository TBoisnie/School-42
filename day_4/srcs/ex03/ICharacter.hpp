/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:38:58 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:19:27 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_CHARACTER_HPP
# define I_CHARACTER_HPP

# include <string>
# include "AMateria.hpp"

class AMateria;

class ICharacter
{
public:
	// Constructors & Destructors
	virtual ~ICharacter() {}

	// Operators

	// Methods
	virtual void equip(AMateria * materia) = 0;
	virtual void unequip(int index) = 0;
	virtual void use(int index, ICharacter & target) = 0;

	// Getters & Setters
	virtual std::string const & getName() const = 0;
};

#endif