/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 19:46:37 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:07:10 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "FragTrap.hpp"

int main()
{
	FragTrap eos("Eos-42");

	{
		FragTrap copy(eos);
		copy = eos;
	}

	std::cout << std::endl;

	eos.meleeAttack("Monstre");
	eos.rangedAttack("Monstre");

	std::cout << std::endl;

	eos.takeDamage(50);
	eos.takeDamage(25);
	eos.beRepaired(30);
	eos.beRepaired(5);

	eos.takeDamage(9000);
	eos.beRepaired(9000);

	std::cout << std::endl;

	eos.vaulthunter_dot_exe("Monstre");
	eos.vaulthunter_dot_exe("Monstre");
	eos.vaulthunter_dot_exe("Monstre");
	eos.vaulthunter_dot_exe("Monstre");

	std::cout << std::endl;

	eos.vaulthunter_dot_exe("Monstre");

	std::cout << std::endl;

	return 0;
}