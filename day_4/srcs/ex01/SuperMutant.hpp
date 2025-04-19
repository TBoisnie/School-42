/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperMutant.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:35:06 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 15:00:43 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPER_MUTANT_HPP
# define SUPER_MUTANT_HPP

# include "Enemy.hpp"

class SuperMutant
	: public Enemy
{
public:
	// Constructors & Destructors
	SuperMutant();
	SuperMutant(const SuperMutant & other);
	~SuperMutant();

	// Operators
	SuperMutant & operator=(const SuperMutant & other);

	// Methods
	void takeDamage(int damage);
};

#endif