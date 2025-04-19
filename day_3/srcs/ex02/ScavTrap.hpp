/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:24:34 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/10 21:31:24 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

# include <string>
# include "ClapTrap.hpp"

class ScavTrap
	: public ClapTrap
{
private:
	ScavTrap();

public:
	// Constructors & Destructors
	ScavTrap(const std::string & name);
	ScavTrap(const ScavTrap & other);
	~ScavTrap();

	// Operators
	ScavTrap & operator=(const ScavTrap & other);

	// Methods
	void challengeNewcomer();
};

#endif