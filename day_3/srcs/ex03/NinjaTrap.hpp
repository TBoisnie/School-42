/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NinjaTrap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 12:37:34 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/10 22:23:58 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NINJA_TRAP_HPP
# define NINJA_TRAP_HPP

# include <string>
# include "ClapTrap.hpp"
# include "FragTrap.hpp"
# include "ScavTrap.hpp"

class NinjaTrap
	: public ClapTrap
{
private:
	NinjaTrap();

public:
	// Constructors & Destructors
	NinjaTrap(const std::string & name);
	NinjaTrap(const NinjaTrap & other);
	~NinjaTrap();

	// Operators
	NinjaTrap & operator=(const NinjaTrap & other);

	// Methods
	void ninjaShoebox(const ClapTrap & clap);
	void ninjaShoebox(const FragTrap & frag);
	void ninjaShoebox(const ScavTrap & scav);
	void ninjaShoebox(const NinjaTrap & ninja);
};

#endif