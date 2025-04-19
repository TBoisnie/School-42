/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/05 18:24:34 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/10 21:31:58 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

# include <string>

class ScavTrap
{
private:
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
	ScavTrap();

public:
	// Constructors & Destructors
	ScavTrap(const std::string & name);
	ScavTrap(const ScavTrap & other);
	~ScavTrap();

	// Operators
	ScavTrap & operator=(const ScavTrap & other);

	// Methods
	void rangedAttack(const std::string & target);
	void meleeAttack(const std::string & target);

	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

	void challengeNewcomer();
};

#endif