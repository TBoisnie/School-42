/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:12:11 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:05:57 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

# include <string>

class FragTrap
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
	FragTrap();

public:
	// Constructors & Destructors
	FragTrap(const std::string & name);
	FragTrap(const FragTrap & other);
	~FragTrap();

	// Operators
	FragTrap & operator=(const FragTrap & other);

	// Methods
	void rangedAttack(const std::string & target);
	void meleeAttack(const std::string & target);

	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);

	void vaulthunter_dot_exe(const std::string & target);

private:
	void pauseAttack(const std::string & target);
	void charmAttack(const std::string & target);
	void magicAttack(const std::string & target);
	void fakeAttack(const std::string & target);
	void ccAttack(const std::string & target);
};

#endif