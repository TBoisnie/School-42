/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 22:07:03 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/11 00:39:57 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "NinjaTrap.hpp"
#include "SuperTrap.hpp"

int main()
{
	/**
	 * FragTrap
	 */
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
	}

	std::cout << "-------------------" << std::endl;

	/**
	 * ScavTrap
	 */
	{
		ScavTrap eos("Eos-43");

		{
			ScavTrap copy(eos);
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

		eos.challengeNewcomer();
		eos.challengeNewcomer();
		eos.challengeNewcomer();
		eos.challengeNewcomer();

		std::cout << std::endl;
	}

	std::cout << "-------------------" << std::endl;

	/**
	 * NinjaTrap
	 */
	{
		NinjaTrap eos("Eos-44");

		{
			NinjaTrap copy(eos);
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

		ClapTrap clap("Clapy");
		FragTrap frag("Fragy");
		ScavTrap scav("Scavy");
		NinjaTrap ninja("Naruto");

		std::cout << std::endl;

		eos.ninjaShoebox(clap);
		eos.ninjaShoebox(frag);
		eos.ninjaShoebox(scav);
		eos.ninjaShoebox(ninja);

		std::cout << std::endl;
	}

	std::cout << "-------------------" << std::endl;

	/**
	 * SuperTrap
	 */
	{
		SuperTrap eos("Eos-45");

		{
			SuperTrap copy(eos);
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

		ClapTrap clap("Clapy");
		FragTrap frag("Fragy");
		ScavTrap scav("Scavy");
		NinjaTrap ninja("Naruto");

		std::cout << std::endl;

		eos.ninjaShoebox(clap);
		eos.ninjaShoebox(frag);
		eos.ninjaShoebox(scav);
		eos.ninjaShoebox(ninja);

		std::cout << std::endl;
	}


	return 0;
}