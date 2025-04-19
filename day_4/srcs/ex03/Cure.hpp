/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:38:56 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/13 02:06:23 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

# include <string>
# include "ICharacter.hpp"

class Cure
	: public AMateria
{
public:
	// Constructors & Destructors
	Cure();
	Cure(const Cure & other);
	~Cure();

	// Operators
	Cure& operator=(const Cure & other);

	// Methods
	AMateria * clone() const;
	void use(ICharacter & target);
};

#endif