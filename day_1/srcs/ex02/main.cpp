/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboisnie <tboisnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 20:24:53 by tboisnie          #+#    #+#             */
/*   Updated: 2020/12/08 01:42:49 by tboisnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ZombieEvent.hpp"

int
main()
{
	ZombieEvent ze = ZombieEvent("Healer");

	std::cout << "Your raid has " << Zombie::alive << " zombie." << std::endl;

	Zombie *healer = ze.newZombie("RaidLeader");
	healer->announce();

	std::cout << "Your raid has " << Zombie::alive << " zombie." << std::endl;

	ze.setZombieType("Tank");

	Zombie *mt1 = ze.randomChump();
	Zombie *mt2 = ze.randomChump();

	std::cout << "Your raid has " << Zombie::alive << " zombies." << std::endl;

	{
		Zombie dps1 = Zombie("Dps", "Dumby1");
		Zombie dps2 = Zombie("Dps", "Dumby2");
		Zombie dps3 = Zombie("Dps", "Dumby3");

		dps1.announce();
		dps2.announce();
		dps3.announce();

		std::cout << "Your raid has " << Zombie::alive << " zombies." << std::endl;

		std::cout << "Dps are dumbs, so they pull before the tank!" << std::endl;
		std::cout << "And of course, they die..." << std::endl;
	}

	std::cout << "Your raid has " << Zombie::alive << " zombies." << std::endl;

	std::cout << "\"WTF! Aggro! Noob Tanks!\" they are yelling." << std::endl;
	std::cout << "Upset, the MT leave the raid." << std::endl;

	delete mt1;

	std::cout << "Your raid has " << Zombie::alive << " zombie." << std::endl;

	std::cout << "R/O" << std::endl;

	delete mt2;
	delete healer;

	std::cout << "Your raid has " << Zombie::alive << " zombie." << std::endl;

	return 0;
}
