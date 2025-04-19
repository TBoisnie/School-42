/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SuperTrap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 17:58:35 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:23:13 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUPER_TRAP_HPP
# define SUPER_TRAP_HPP

# include <string>
# include "FragTrap.hpp"
# include "NinjaTrap.hpp"

class SuperTrap
	: public FragTrap,
	  public NinjaTrap
{
private:
	SuperTrap();

public:
	// Constructors & Destructors
	SuperTrap(const std::string & name);
	SuperTrap(const SuperTrap & other);
	~SuperTrap();

	// Operators
	SuperTrap& operator=(const SuperTrap & other);

	// Methods
	void rangedAttack(const std::string & target);
	void meleeAttack(const std::string & target);
};

#endif