/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PowerFist.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:46:13 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 15:00:00 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POWER_FIST_HPP
# define POWER_FIST_HPP

# include "AWeapon.hpp"

class PowerFist
	: public AWeapon
{
public:
	// Constructors & Destructors
	PowerFist();
	PowerFist(const PowerFist & other);
	~PowerFist();

	// Operators
	PowerFist & operator=(const PowerFist & other);

	// Methods
	void attack() const;
};

#endif