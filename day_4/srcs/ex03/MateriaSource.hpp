/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:38:49 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:46:27 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIA_SOURCE_HPP
# define MATERIA_SOURCE_HPP

# include <string>
# include "IMateriaSource.hpp"
# include "AMateria.hpp"

class MateriaSource
	: public IMateriaSource
{
	static const int MAX_LEARN = 4;

private:
	// Attributes
	AMateria * materias[MAX_LEARN];

public:
	// Constructors & Destructors
	MateriaSource();
	MateriaSource(const MateriaSource & other);
	~MateriaSource();

	// Operators
	MateriaSource & operator=(const MateriaSource & other);

	// Methods
	void learnMateria(AMateria * materia);
	AMateria * createMateria(std::string const & type);
};

#endif