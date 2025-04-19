/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 21:28:26 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:21:51 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

# include <string>

class ClapTrap
{
protected:
	// Attributes
	std::string name;

	unsigned int level;
	unsigned int hit_points;
	unsigned int max_hit_points;
	unsigned int energy_points;
	unsigned int max_energy_points;
	unsigned int melee_attack_damage;
	unsigned int ranged_attack_damage;
	unsigned int armor_damage_reduction;

private:
	ClapTrap();

public:
	// Constructors & Destructors
	ClapTrap(const std::string & name);
	ClapTrap(const ClapTrap & other);
	virtual ~ClapTrap();

	// Operators
	ClapTrap & operator=(const ClapTrap & other);

	// Methods
	void rangedAttack(const std::string & target);
	void meleeAttack(const std::string & target);

	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);
};

#endif