/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:38:53 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:15:48 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

# include <string>
# include "ICharacter.hpp"

class Ice
	: public AMateria
{
public:
	// Constructors & Destructors
	Ice();
	Ice(const Ice & other);
	~Ice();

	// Operators
	Ice & operator=(const Ice & other);

	// Methods
	AMateria * clone() const;
	void use(ICharacter & target);
};

#endif
