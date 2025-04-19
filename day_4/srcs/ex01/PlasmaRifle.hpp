/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlasmaRifle.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:46:10 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/12 16:22:29 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLASMA_RIFLE_HPP
# define PLASMA_RIFLE_HPP

# include "AWeapon.hpp"

class PlasmaRifle
	: public AWeapon
{
public:
	// Constructors & Destructors
	PlasmaRifle();
	PlasmaRifle(const PlasmaRifle & other);
	~PlasmaRifle();

	// Operators
	PlasmaRifle & operator=(const PlasmaRifle & other);

	// Methods
	void attack() const;
};

#endif