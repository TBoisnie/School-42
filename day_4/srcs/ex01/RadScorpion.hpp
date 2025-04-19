/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RadScorpion.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:31:31 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 15:00:23 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAD_SCORPION_HPP
# define RAD_SCORPION_HPP

# include "Enemy.hpp"

class RadScorpion
	: public Enemy
{
public:
	// Constructors & Destructors
	RadScorpion();
	RadScorpion(const RadScorpion & other);
	~RadScorpion();

	// Operators
	RadScorpion & operator=(const RadScorpion & other);

	// Methods
	void takeDamage(int damage);
};

#endif