/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:10:23 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:09:14 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef A_MATERIA_HPP
# define A_MATERIA_HPP

# include <string>
# include "ICharacter.hpp"

class ICharacter;

class AMateria
{
private:
	// Attributes
	unsigned int _xp;
	std::string type;

private:
	AMateria();

public:
	// Constructors & Destructors
	AMateria(std::string const & type);
	AMateria(const AMateria & other);
	virtual ~AMateria();

	// Operators
	AMateria& operator=(const AMateria & other);

	// Methods
	virtual AMateria * clone() const = 0;
	virtual void use(ICharacter & target);

	// Getters & Setters
	const std::string & getType() const;
	unsigned int getXP() const;
	void setXP(unsigned int xp);
};

#endif