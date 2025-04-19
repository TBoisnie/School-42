/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:38:46 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:44:28 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I_MATERIA_SOURCE_HPP
# define I_MATERIA_SOURCE_HPP

# include <string>
# include "AMateria.hpp"

class IMateriaSource
{
public:
	// Constructors & Destructors
	virtual ~IMateriaSource() {}

	// Operators

	// Methods
	virtual void learnMateria(AMateria * materia) = 0;
	virtual AMateria * createMateria(std::string const & type) = 0;
};

#endif